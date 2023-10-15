const express = require('express');
const lame = require('lame');
const Speaker = require('speaker');
//const pulse = require('pulseaudio2');
var PulseAudio = require('pulseaudio2');
const fs = require('fs');

const app = express();
const port = 3000;

app.get('/audio.mp3', (req, res) => {
    // Capture audio using PulseAudio
    var context = new PulseAudio();
    //var player = context.createPlaybackStream();
    // player.write(data);
    // player.on('drain', function () {
    //     player.end();
    // });

    const pulseAudioStream = context.createRecordStream({
        stream: "A.U.D.I.B.L.E Node JS Web Server",                         // optional stream name ("node-stream" by default)
        device: "alsa_output.usb-Yamaha_Corporation_Steinberg_UR22mkII-00.iec958-stereo.monitor",                       // optional device name
        latency: 0,
      });//.createCaptureStream();

    // Encode audio to MP3
    const mp3Encoder = new lame.Encoder({
        channels: 2,
        bitDepth: 16,
        sampleRate: 44100,
    });

    pulseAudioStream.pipe(mp3Encoder);

    // Stream the MP3 audio to the client
    mp3Encoder.pipe(res);
});

app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});
