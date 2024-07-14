import matplotlib.pyplot as plt
import numpy as np

sample_rate = 6/200 # 取樣週期
point = 200 # 取樣點數

# 定義函數
def f(x):
    return 10 * np.sin(2 * np.pi * x) + 2 * np.sin(16 * np.pi * x)

def resample(sample_rate, point):
    # 採樣，存到sample_values這個list當中
    sample_values = []
    sample_points = []  # 存取樣點的x座標
    for i in range(point):
        x = i * sample_rate
        sample_points.append(x)
        y = f(x)
        sample_values.append(y)

    # 畫出函數圖像需要的(x,y)
    x = np.linspace(0, 6, 1000)
    y = f(x)

    # 绘制函数图像和取样点
    plt.figure(figsize=(10, 6))
    plt.plot(x, y, label='f(x) = 10sin(2πx) + 2sin(16πx)', linewidth=2)
    plt.scatter(sample_points, sample_values, color='red', label='Sample Points')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.title('Function Plot and Sample Points')
    plt.legend()
    plt.grid(True)
    plt.show()

    return sample_values

def draw_dft(x):
    t_axis = np.arange(0, 6, sample_rate)  # 時間軸，從 0 到 6 秒，以 sample_rate 為一間隔
    dt = 0.005  # 時間間隔
    f_axis = np.arange(-10, 10, dt)  # 頻率軸，從 -10 到 10 Hz，每 0.005 Hz 為一間隔
    X = np.zeros(len(f_axis), dtype=complex)  # 預先配置好歸零陣列空間
    
    # 進行 CTFT 計算
    for iFreq in range(len(f_axis)):
        for iTime in range(len(t_axis)):
            X[iFreq] += x[iTime] * np.exp(-1j * 2 * np.pi * f_axis[iFreq] * t_axis[iTime]) * dt

    # 計算頻譜量值 (magnitude)
    mag_X = np.abs(X)

    plt.figure(figsize=(10, 6))
    plt.plot(f_axis, mag_X, label='Magnitude Spectrum', linewidth=2)
    plt.yticks(np.arange(0, 37, 6))
    plt.ylim([0, 36])
    plt.xlabel('Frequency')
    plt.ylabel('Amplitude')
    plt.title('Discrete Fourier Transform')
    plt.show()

def filter():
    f_axis = np.arange(-4, 4 , 0.005)
    # 定義 Heaviside 函數 (step-function)
    H = np.heaviside(f_axis + 3, 0) - np.heaviside(f_axis - 3, 0)  # 頻譜

    # 畫圖
    plt.figure()
    plt.plot(f_axis, H, linewidth=3)
    plt.xlabel('Frequency (Hz)')
    plt.ylabel('abs(H(f))')
    plt.title('Magnitude Spectrum of H(f)')
    plt.show()

    return f_axis, H

def IDFT(f_axis, H):
    t_axis = np.arange(-10, 10, 0.005)
    h = np.zeros(len(t_axis), dtype=complex)
    for iTime in range(len(t_axis)):
        for iFreq in range(len(H)):
            h[iTime] += H[iFreq] * np.exp(1j * 2 * np.pi * f_axis[iFreq] * t_axis[iTime]) * 0.005

    plt.figure(figsize=(10, 6))
    plt.plot(t_axis, h, label='Magnitude Spectrum', linewidth=2)
    plt.xlabel('time')
    plt.ylabel('h(t)')
    plt.title('Inverse Discrete Fourier Transform')
    plt.show()

x = resample(sample_rate, point)
draw_dft(x)
f_axis, H = filter()
IDFT(f_axis, H)