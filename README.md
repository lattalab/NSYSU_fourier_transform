### NSYSY_CALCULUS（II）
110-2 spring course.
This project was made at 2022/05 as the final project report for `CALCULUS(II)`.

The only `cpp` file was the original written version that simplely implement the DFT.

The other part want to explain more about the concept.  
Note: this project are mainly considered at https://alan23273850.gitbook.io/signals-and-systems/di-san-zhang-lian-xu-shi-jian-de-xun-hao-chu-li/di-er-jie-xun-hao-chu-li-fan-li-zhan-shi

* figure 1: 原始時域訊號 + 加上採樣點
* figure 2: 採樣後，透過DFT進行轉成頻譜圖
* filter : 設計出一個在頻域上的濾波器函數，在這邊我們將remove掉 `-3~3範圍之外的頻率`。
* filter_in_time_domain : 用IDFT還原得出時域訊號

然而這個濾波器的時域訊號可以用傅立葉轉換的對稱性推出，由下圖看出這兩個函數有某種關聯，而他們各自的傅立葉轉換也能算出來。  
但自行設計的filter在頻域的函數發現跟`G(w)`只差了`2pi`，我們可以在時域跟頻域同除`2pi`，並不會影響轉換後的結果。  
![image](https://github.com/user-attachments/assets/726d3caa-6bf2-4d79-8452-782e6fc03ea6)

之後想要驗證`時域函數卷積 = 頻域函數相乘`的概念 (但程式圖僅供參考，這邊有點失真)
* conv.png : 驗證convolution的結果
* filtered.png : 將卷積後的結果轉回頻域看看，是否成功過濾 (只留下-3~3範圍內的頻率)
![image](https://github.com/user-attachments/assets/66ea6d14-636d-4fba-910b-c2404d606e9b)
![image](https://github.com/user-attachments/assets/f48a9f4c-6fc0-4195-b628-ce4407dfdf47)

## Result
![image](https://github.com/user-attachments/assets/8f55ceb4-ae52-4f93-9542-855225cdf038)
![image](https://github.com/user-attachments/assets/2e5003d9-da2a-4a5c-a7bd-e85b6c17f3d1)

This project 簡單的呈現出如何分析頻譜，以及設計簡單的濾波器進行過濾，以簡單函數的進行試驗。  

