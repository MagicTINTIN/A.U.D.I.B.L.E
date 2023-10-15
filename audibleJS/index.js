const express = require('express');
const lame = require('lame');
var PulseAudio = require('pulseaudio2');
const readline = require('readline');
const fs = require('fs');

const app = express();
const port = 3000;

async function getFirstLine(pathToFile) {
    const readable = fs.createReadStream(pathToFile);
    const reader = readline.createInterface({ input: readable });
    const line = await new Promise((resolve) => {
        reader.on('line', (line) => {
            reader.close();
            resolve(line);
        });
    });
    readable.close();
    return line;
}
let devicechosen;

getFirstLine("./source.cfg").then((val) => {
    devicechosen = val;

    console.log(`Device captured : ${devicechosen}`);
    app.get('/Audible.mp3', (req, res) => {
        var context = new PulseAudio();

        const pulseAudioStream = context.createRecordStream({
            stream: "A.U.D.I.B.L.E Node JS Web Server",
            device: devicechosen,
            latency: 0,
        });

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

})

app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});
