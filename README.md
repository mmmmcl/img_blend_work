<!--
 * @Date: 2024-03-23 22:40:15
 * @LastEditors: gyt vocvocal@163.com
 * @LastEditTime: 2024-04-21 20:08:28
 * @FilePath: /img_fusion/README.md
-->
# 信息融合大作业1
## 拉普拉斯金字塔图像融合
- 依赖解决（ubuntu 20.04 22.04）：
```
sudo apt install cmake gcc libopencv-dev
```
一键运行：
```
 git clone https://github.com/mmmmcl/img_blend_work.git

 cd img_blend_work

 mkdir build
 
 cd build

 cmake ..

 make

 ./main
```
### 效果展示

原始图片：

   ![](./data/pic1.png)
   ![](./data/pic2.png)
   
融合后（15层塔）：

   ![](./data/blend.png)
   
   