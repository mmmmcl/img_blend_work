import numpy as np
import matplotlib.pyplot as plt

# 读取txt文件
data = np.genfromtxt('../result.txt')

# 提取数据
height_measurements = data[:, 0]
filtered_height = data[:, 1]
filtered_velocity = data[:, 2]

# 创建画布
plt.figure(figsize=(10, 6))

# 绘制测量高度和滤波后高度
plt.plot(height_measurements, label='Height Measurements', color='blue', linestyle='--', marker='o')
plt.plot(filtered_height, label='Filtered Height', color='orange', linestyle='-', marker='x')

# 添加图例和标签
plt.title('Height vs. Filtered Height')
plt.xlabel('Time')
plt.ylabel('Height (m)')
plt.legend()

# 调整y轴比例尺，增加一些余量
plt.ylim(min(height_measurements.min(), filtered_height.min()) - 10, max(height_measurements.max(), filtered_height.max()) + 10)

# 显示图形
plt.grid(True)
plt.tight_layout()
plt.show()
# 创建另外一张图
plt.figure(figsize=(10, 6))

# 绘制滤波后速度
plt.plot(filtered_velocity, label='Filtered Velocity', color='green', linestyle='-', marker='s')

# 添加图例和标签
plt.title('Filtered Velocity')
plt.xlabel('Time')
plt.ylabel('Velocity (m/s)')
plt.legend()

# 调整y轴比例尺，增加一些余量
plt.ylim(filtered_velocity.min() - 10, filtered_velocity.max() + 10)

# 显示图形
plt.grid(True)
plt.tight_layout()
plt.show()
