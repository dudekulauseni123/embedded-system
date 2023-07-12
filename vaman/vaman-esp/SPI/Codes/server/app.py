import flask

msg = ""

app = flask.Flask(__name__)
@app.route('/spi', methods=['GET', 'POST'])
def status_handler():
    global msg
    if flask.request.method == 'GET':
        return "Received from Arduino: " + str(msg)
    elif flask.request.method == 'POST':
        msg = flask.request.json['message']
        return {}
