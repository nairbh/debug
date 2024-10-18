#!/usr/bin/python3
"""
    Module that sets up a basic HTTP Server
"""

from http.server import HTTPServer, BaseHTTPRequestHandler
import json


class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):
    """
    Class that creates a simple server
    """

    def do_GET(self):
        """
        Method that handles GET requests
        """
        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            self.wfile.write(b'Hello, this is a simple API!')
        elif self.path == '/data':
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            data = {
                "name": "John",
                "age": 30,
                "city": "New York"
            }
            self.wfile.write(json.dumps(data).encode("utf-8"))
        elif self.path == '/info':
            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            data = {
                "version": "1.0",
                "description": "A simple API built with http.server"
            }
            self.wfile.write(json.dumps(data).encode("utf-8"))
        elif self.path == "/status":
            self.send_response(200)
            self.send_header("Content-type", "text/plain")
            self.end_headers()
            self.wfile.write(b"OK")
        else:
            # Envoi d'une réponse 404 basique
            self.send_response(404)
            self.send_header('Content-type', 'text/plain')
            self.end_headers()
            # Message simplifié pour correspondre à ce que le test pourrait attendre
            self.wfile.write(b'404 Not Found\n')


def run(
        server_class=HTTPServer,
        handler_class=SimpleHTTPRequestHandler,
        port=8000):
    """ Function that runs the server """
    server_address = ('localhost', port)
    httpd = server_class(server_address, handler_class)
    httpd.serve_forever()


if __name__ == "__main__":
    """
    Main function that runs the server
    """
    run()
