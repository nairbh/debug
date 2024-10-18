#!/usr/bin/python3
""" Modules mixes requests csv and json module."""

import requests
import json
import csv


def fetch_and_print_posts():
    """Fetch and prints status code.
    Parse data into json
    print out object titles.
    """

    get = requests.get('https://jsonplaceholder.typicode.com/posts')
    print("Status Code:", get.status_code)

    if get.status_code == 200:
        posts = get.json()

    for post in posts:
        print(post['title'])


def fetch_and_save_posts():
    """Fetch and save posts in csv."""

    get = requests.get('https://jsonplaceholder.typicode.com/posts')

    if get.status_code == 200:
        posts = get.json()
        formated_data = [{"id": post["id"],
                          "title": post["title"],
                          "body": post["body"]} for post in posts]

        with open("posts.csv", mode="w", newline="", encoding="utf-8") as dic:
            write_to_file = csv.DictWriter(
                dic, fieldnames=["id", "title", "body"])
            write_to_file.writeheader()
            write_to_file.writerows(formated_data)

fetch_and_print_posts()
