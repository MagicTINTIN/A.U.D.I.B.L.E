#include <iostream>
#include <boost/asio.hpp>
#include <pulse/simple.h>

constexpr int SAMPLE_RATE = 44100;
constexpr int FRAME_SIZE = 1024;

int main() {
    boost::asio::io_service io_service;
    boost::asio::ip::udp::socket socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 12345));
    boost::asio::ip::udp::endpoint remote_endpoint;

    pa_sample_spec sample_spec;
    sample_spec.format = PA_SAMPLE_S16LE;
    sample_spec.rate = SAMPLE_RATE;
    sample_spec.channels = 2;

    pa_simple *s = nullptr;
    int error;

    if (!(s = pa_simple_new(nullptr, "DesktopAudioCapture", PA_STREAM_RECORD, nullptr, "audio", &sample_spec, nullptr, nullptr, &error))) {
        std::cerr << "pa_simple_new() failed: " << pa_strerror(error) << std::endl;
        return 1;
    }

    while (true) {
        int16_t buf[FRAME_SIZE * 2];
        if (pa_simple_read(s, buf, sizeof(buf), &error) < 0) {
            std::cerr << "pa_simple_read() failed: " << pa_strerror(error) << std::endl;
            pa_simple_free(s);
            return 1;
        }

        socket.receive_from(boost::asio::buffer(buf, sizeof(buf)), remote_endpoint);
    }

    pa_simple_free(s);
    return 0;
}
