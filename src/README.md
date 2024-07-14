This src file was not included in previos project , you can say that this is another project that related to `fourier transfer`.

you just type `make` with makefile that complier with FFT.cpp to get the executable file.

* CH_fake_noise.wav : a sampled audio file that contain some noise behind
* CH_fake_denoise.wav : this audio has been processed by python library `noisereduce`
* denoised_output.wav : from CH_fake_noise.wav and do some own modified
* some spectrum show how the frequency and amplitude distribute

* FFT.cpp
  * implement FFT logic with `divide and conquer` algorithm.
  * implement IFFT with math understanding $IFFT(x) = \frac{1}{N} conj( conj (FFT(x)) )$
  * use `sndfile` in c/c++ language to read/write audio file
  * modify() : a function modify the frequency-amplitude, filtered out the lower amplitude frequency, then modify the other amplitude value
 
## result
This project simply do how to deal with the spectrum value.
The original goal was created self-own denoise algorithm with FFT , but failed.
