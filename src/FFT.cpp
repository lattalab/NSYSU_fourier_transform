#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <sndfile.hh>   // read audio file
#include <fstream>
#include <gnuplot-iostream.h>

#define pi acos(-1)
using namespace std;
// rename
using Complex = complex<double>;
using CArray = vector<Complex>;

// FFT function
void fft(CArray& x) {
    const size_t N = x.size();
    if (N <= 1) return;

    // Divide
    CArray even(N/2), odd(N/2);
    for (size_t i = 0; i < N/2; ++i) {
        even[i] = x[i*2];
        odd[i] = x[i*2 + 1];
    }

    // Conquer
    fft(even);
    fft(odd);

    // Combine
    for (size_t i = 0; i < N/2; ++i) {
        Complex t = polar(1.0, -2 * pi * i / N) * odd[i];
        x[i] = even[i] + t;
        x[i + N/2] = even[i] - t;
    }
}

void draw_spectrum(CArray& res, int sample_rate)
{
    // 繪製頻譜圖
    Gnuplot gp;
    gp << "set xlabel 'Frequency'\nset ylabel 'Magnitude'\n";
    gp << "plot '-' with lines title 'FFT Result'\n";
    for (size_t i = 0; i < res.size(); ++i) {
        gp << i * sample_rate / res.size() << " " << abs(res[i]) << "\n";
    }
    gp << "e\n";    // end
}

void modify(CArray& res, double threshold)
{
    // remove some lower frequency
    for (size_t i =0; i<res.size(); ++i){
        if (abs(res[i]) < threshold){
            res[i] = complex<double>();
        }
    }

    // 放大剩餘頻率並進行縮放
    int window_size = 10;  // 窗口大小
    for (size_t i = 0; i < res.size(); i = i + window_size) {

            // 計算鄰近頻率的平均值
            double sum = 0;
            int count = 0;
            for (int j = 0; j < window_size; ++j) {
                int idx = i + j;
                sum += abs(res[idx]);
                count++;
            }
            double avg = sum / count;

            // 根據鄰近頻率的平均值進行縮放
            for (int j = 0; j < window_size; ++j) {
                int idx = i + j;
                if (abs(res[idx]) > avg) {
                    res[idx] -= (0.5*avg);
                } else {
                    res[idx] = 7.0 * res[idx] + avg;
                }
            }
    }
}

void ifft(CArray &x){
    const size_t N = x.size();

    // Take conjugate of the complex numbers
    for (int i = 0; i < N; ++i) {
        x[i] = conj(x[i]);
    }

    // Apply FFT
    fft(x);

    // Take conjugate again and divide by N
    for (int i = 0; i < N; ++i) {
        x[i] = conj(x[i]) / static_cast<double>(N);
    }
}

int main()
{
    // 讀取音訊檔案
    // set your filename path
    string filename = "CH_fake_noise.wav";   // supported wav file only.
    SndfileHandle file(filename);
    if (file.error()) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    int sample_rate = file.samplerate();    // get sample rate
    vector<double> signal(file.frames());   // create a vector called signal with default size file.frames()
    file.read(signal.data(), signal.size());    // read data to signal

    // 計算 FFT
    CArray fft_result(signal.begin(), signal.end());    // pass signal to complex vector CArray
    fft(fft_result);
    draw_spectrum(fft_result, sample_rate);

    // try modify the spectrum
    modify(fft_result, 5);
    draw_spectrum(fft_result, sample_rate);

    // 計算 IFFT
    ifft(fft_result);
     // 將 IFFT 的結果轉換回實數格式
    vector<double> reconstructed_signal(fft_result.size());
    for (size_t i = 0; i < fft_result.size(); ++i) {
        reconstructed_signal[i] = fft_result[i].real();
    }

    // 將實數數據寫入新的音訊文件
    SndfileHandle outFile("denoised_output.wav", SFM_WRITE, file.format(), file.channels(), sample_rate);
    if (outFile.error()) {
        std::cerr << "Error: could not open output file." << std::endl;
        return 1;
    }
    outFile.write(reconstructed_signal.data(), reconstructed_signal.size());


    return 0;
}