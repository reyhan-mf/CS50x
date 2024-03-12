import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    getUser = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    getUsername = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    username = getUsername[0]["username"]
    getTransactions = db.execute("SELECT * FROM transactions WHERE username = ?", username)
    getTransactions = getTransactions[::-1]
    transaction_data = {}
    totalBought = 0  # Initialize totalBought to 0

    for transaction in getTransactions:
        symbol = transaction["symbol"]
        shares = transaction["shares"]
        price = transaction["price"]
        total = price * shares

        if symbol in transaction_data:
            transaction_data[symbol]["shares"] += shares

        else:
            transaction_data[symbol] = {"shares": shares, "price": price, "total": total}
            totalBought += total
    cash=getUser[0]["cash"]

    return render_template("index.html", transactions=transaction_data.items(), cash=cash, totalBought=totalBought + cash)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":

        userCash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        username  = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]

        symbol = request.form.get("symbol")
        shares_inputted = (request.form.get("shares"))

        if not symbol:
            return apology("Missing Symbol", 400)
        if not shares_inputted:
            return apology("Missing Input Share", 400)

        try:
            shares_inputted = float(request.form.get("shares"))
        except ValueError:
            return apology("Shares must be a number", 400)


        if shares_inputted < 0:
            return apology("shares can't be negative!", 400)
        shares = lookup(symbol)

        if not shares:
            return apology("Missing Share", 400)

        if shares_inputted != int(shares_inputted):
            return apology("Shares must be a whole number", 400)

        price = shares["price"]
        purchased = (shares_inputted * price)


        if purchased > userCash:
            return apology("Can't Afford", 400)


        time = datetime.datetime.now()
        existing_symbol = db.execute("SELECT symbol FROM transactions WHERE username = ? AND symbol = ?", username, symbol)

        if existing_symbol:

            db.execute("UPDATE transactions SET shares = shares + ?, price = ? WHERE username = ? AND symbol = ?",
                    shares_inputted, price, username, symbol)

            db.execute("INSERT INTO history (username, transaction_type, symbol, shares, price, timestamp) VALUES(?, ?, ?, ?, ?, ?)",
                    username, "buy", symbol, shares_inputted, price, time)


        else:

            db.execute("INSERT INTO transactions (username,  symbol, shares, price) VALUES(?, ?, ?, ?)",
                    username, symbol, shares_inputted, price)

            db.execute("INSERT INTO history (username, transaction_type, symbol, shares, price, timestamp) VALUES(?, ?, ?, ?, ?, ?)",
                    username, "buy", symbol, shares_inputted, price, time)


        db.execute("UPDATE users SET cash = ? WHERE username = ?", (userCash - purchased), username)
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    userCash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    username  = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    symbolBought = db.execute("SELECT symbol FROM transactions WHERE username = ?", username)

    time = datetime.datetime.now()

    if request.method == "GET":
        return render_template("sell.html", symbolBought=symbolBought)

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares_inputted = (request.form.get("shares"))
        stored_shares = db.execute("SELECT shares FROM transactions WHERE username = ? AND symbol = ?", username, symbol)

        # print(f"stored: {stored_shares} and {symbol}")

        if not symbol:
            return apology("Missing Symbol", 400)
        if not shares_inputted:
            return apology("Missing Input Share", 400)

        try:
            shares_inputted = float(request.form.get("shares"))
        except ValueError:
            return apology("Shares must be a number", 400)

        if shares_inputted >= stored_shares[0]["shares"]:
            return apology("Too many shares", 400)
        if shares_inputted < 0:
            return apology("shares can't be negative!", 400)
        shares = lookup(symbol)

        price = shares["price"]
        purchased = (shares_inputted * price)

        if not shares:
            return apology("Missing Share", 400)

        if shares_inputted != int(shares_inputted):
            return apology("Shares must be a whole number", 400)

        existing_symbol = db.execute("SELECT symbol FROM transactions WHERE username = ? AND symbol = ?", username, symbol)

        if existing_symbol:

            db.execute("UPDATE transactions SET shares = shares - ?, price = ? WHERE username = ? AND symbol = ?",
                    shares_inputted, price, username, symbol)

            db.execute("INSERT INTO history (username, transaction_type, symbol, shares, price, timestamp) VALUES(?, ?, ?, ?, ?, ?)",
                    username, "sell", symbol, -1*shares_inputted, price, time)


        else:

            db.execute("INSERT INTO transactions (username,  symbol, shares, price) VALUES(?, ?, ?, ?)",
                    username, symbol, shares_inputted, price)

            db.execute("INSERT INTO history (username, transaction_type, symbol, shares, price, timestamp) VALUES(?, ?, ?, ?, ?, ?)",
                    username, "sell", symbol, -1*shares_inputted, price, time)


        db.execute("DELETE FROM transactions WHERE username = ? AND symbol = ? AND shares <= 0", username , symbol)

        db.execute("UPDATE users SET cash = ? WHERE username = ?", (userCash + purchased), username)
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    getUser = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    getUsername = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    username = getUsername[0]["username"]
    getHistory = db.execute("SELECT * FROM history WHERE username = ?", username)

    return render_template("history.html", history = getHistory)


@app.route("/changepass", methods=["GET", "POST"])
def changePass():
    if request.method == "GET":
        return render_template("changepass.html")
    if request.method == "POST":
        rows = db.execute("SELECT * FROM users")
        users = []
        for row in rows:
            users.append(row["username"])
        if request.method == "POST":
            username = request.form.get("username")
            password = request.form.get("password")
            confirmation = request.form.get("confirmation")

            if not password or not confirmation:
                return apology("All field must be filled", 400)
            if not (password == confirmation):
                return apology("Password and Confirmation must match", 400)

            db.execute("UPDATE users SET hash = ? WHERE username = ?", generate_password_hash(password, method='pbkdf2', salt_length=16), username)

            flash("Password Changed!")

            return redirect("/")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]


        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        symbol_submitted = request.form.get("symbol")
        if not symbol_submitted:
            return apology("400")

        symbol = lookup(symbol_submitted)
        if not symbol:
            return apology("400")

        return render_template("quoted.html", symbol=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    rows = db.execute("SELECT * FROM users")
    users = []
    for row in rows:
        users.append(row["username"])
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if username in users:
            return apology("Username already taken", 400)
        if not username or not password or not confirmation:
            return apology("All field must be filled", 400)
        if not (password == confirmation):
            return apology("Password and Confirmation must match", 400)

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password, method='pbkdf2', salt_length=16))

        flash("Registered!")

        return redirect("/")


    return render_template("registers.html")



