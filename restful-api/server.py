#!/usr/bin/python3

import http.server
import socketserver
import requests
import json

PORT = 8000
Handler = http.server.SimpleHTTPRequestHandler
 
with socketserver.TCPServer(("", PORT), Handler) as httpd:
     print("serving at port", PORT)
     httpd.serve_forever()


class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):


    def do_GET(self):

        if self.path == "/":
            self.send_response(200)
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(b"Hello, this is a simple API!")

        elif self.path =="/data":
            self.send_response(200)
            self.send_header("Content-type", "application/json")
            self.end_headers()

            data = {
                    "name": "John",
                    "age": 30,
                    "city": "New York"
                    }

            self.wfile.write(json.dumps(data).encode("utf-8"))

        else:
            self.send_response(404)
            self.end_headers()
