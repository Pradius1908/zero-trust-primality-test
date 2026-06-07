from flask import Flask
from flask import render_template
from flask import request

import csv
import os

from services.prime_engine import generate_rsa

app = Flask(__name__)

DB_FOLDER = "database"

USERS_DB = os.path.join(
    DB_FOLDER,
    "users.csv"
)

CERT_DB = os.path.join(
    DB_FOLDER,
    "certificates.csv"
)


def initialize_database():

    os.makedirs(
        DB_FOLDER,
        exist_ok=True
    )

    if not os.path.exists(USERS_DB):

        with open(
            USERS_DB,
            "w",
            newline=""
        ) as file:

            writer = csv.writer(file)

            writer.writerow([
                "username"
            ])

    if not os.path.exists(CERT_DB):

        with open(
            CERT_DB,
            "w",
            newline=""
        ) as file:

            writer = csv.writer(file)

            writer.writerow([
                "username",
                "n",
                "e"
            ])


initialize_database()


@app.route("/")
def home():

    return render_template(
        "index.html"
    )


@app.route(
    "/register",
    methods=["GET", "POST"]
)
def register():

    if request.method == "POST":

        username = (
            request.form["username"]
            .strip()
            .lower()
        )

        keypair = generate_rsa()

        with open(
            USERS_DB,
            "a",
            newline=""
        ) as file:

            writer = csv.writer(file)

            writer.writerow([
                username
            ])

        with open(
            CERT_DB,
            "a",
            newline=""
        ) as file:

            writer = csv.writer(file)

            writer.writerow([
                username,
                keypair["n"],
                keypair["e"]
            ])

        return render_template(
            "certificate.html",
            username=username,
            keypair=keypair
        )

    return render_template(
        "register.html"
    )


@app.route(
    "/login",
    methods=["GET", "POST"]
)
def login():

    if request.method == "POST":

        username = (
            request.form["username"]
            .strip()
            .lower()
        )

        found = False

        with open(
            CERT_DB,
            newline=""
        ) as file:

            reader = csv.DictReader(file)

            for row in reader:

                csv_user = (
                    row["username"]
                    .strip()
                    .lower()
                )

                if csv_user == username:

                    found = True
                    break

        return render_template(
            "login.html",
            authenticated=found
        )

    return render_template(
        "login.html"
    )


@app.route("/dashboard")
def dashboard():

    users = []

    with open(
        CERT_DB,
        newline=""
    ) as file:

        reader = csv.DictReader(file)

        for row in reader:

            users.append(row)

    return render_template(
        "dashboard.html",
        users=users
    )


if __name__ == "__main__":

    app.run(
        host="0.0.0.0",
        port=5000,
        debug=True
    )