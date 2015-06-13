var express = require('express');
var logger = require('morgan');

var app = express();

app.use(logger('dev'));

// API routes

// PING - Check if server is up
app.get('/ping', function (req, res) {

    res.json({
        "ok": true
    });

});

// START - Start the game
app.get('/start', function (req, res) {

    var my_pos = req.query.y.split('|');
    var opponent_pos = req.query.o.split('|');
    var gridSize = req.query.g;

    console.log("my_pos = " + my_pos);
    console.log("opponent_pos = " + opponent_pos);
    console.log("gridSize = " + gridSize);

    res.json({
        "ok": true
    });

});

// PLAY - Play a move
app.get('/play', function (req, res) {

    var opponent_move = req.query.m.split('|');

    console.log("opponent_move = " + opponent_move);

    res.json({
        "m": "1|2" // TEMPORARILY HARDCODED
    });

});

// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});

// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.json({
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.json({
        message: err.message,
        error: err
    });
});


module.exports = app;
