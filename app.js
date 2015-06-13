var express = require('express');
var logger = require('morgan');
var spawn = require('child_process').spawn;

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

    var proc = spawn(
        'bin/game', 
        ["start", my_pos[0], my_pos[1], opponent_pos[0], opponent_pos[1], gridSize]
    );

    proc.on('error', function(err) {
        console.log('error ' + err);
    });

    proc.on('close', function(code) {
        console.log('process exit code ' + code);
    });

    res.json({
        "ok": true
    });

});

// PLAY - Play a move
app.get('/play', function (req, res) {

    var opponent_move = req.query.m.split('|');

    console.log("opponent_move = " + opponent_move);

    var proc = spawn('bin/game', ["play", opponent_move[0], opponent_move[1]]);

    proc.stdout.setEncoding('utf8');

    proc.stdout.on('data', function(outputData) {

        console.log("outputData = " + outputData);

        my_move = outputData.trim().split(" ").join('|');

        console.log("my_move = " + my_move);

        res.json({
            "m": my_move
        });

    });

    proc.on('error', function(err) {
        console.log('error ' + err);
    });

    proc.on('close', function(code) {
        console.log('process exit code ' + code);
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
