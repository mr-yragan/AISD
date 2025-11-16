import subprocess
import matplotlib.pyplot as plt
import math
import csv

N_values = list(range(100, 100001, 500))
exact_area = 0.25 * math.pi + 1.25 * math.asin(0.8) - 1

c1_x, c1_y, c1_r = 1.0, 1.0, 1.0

c2_x, c2_y = 1.5, 2.0
c2_r = math.sqrt(5) / 2

c3_x, c3_y = 2.0, 1.5
c3_r = math.sqrt(5) / 2  

circles_input = f"{c1_x} {c1_y} {c1_r}\n{c2_x} {c2_y} {c2_r}\n{c3_x} {c3_y} {c3_r}\n"

estimated_areas_wide = []
estimated_areas_narrow = []

print(f"exact_area: {exact_area:.15f}")

for idx, N in enumerate(N_values):
    input_wide = circles_input + f"{N}\n"
    result_wide = subprocess.run(
        ['monte_carlo_wide.exe'],
        input=input_wide,
        capture_output=True,
        text=True
    )
    area_wide = float(result_wide.stdout.strip())
    estimated_areas_wide.append(area_wide)

    input_narrow = circles_input + f"{N}\n"
    result_narrow = subprocess.run(
        ['monte_carlo_narrow.exe'],
        input=input_narrow,
        capture_output=True,
        text=True
    )
    area_narrow = float(result_narrow.stdout.strip())
    estimated_areas_narrow.append(area_narrow)

    if (idx + 1) % 10 == 0:
        print(f"[{idx + 1}/{len(N_values)}] N={N:6d} | Wide={area_wide:.15f} | Narrow={area_narrow:.15f}")


with open('results.csv', 'w', newline='', encoding='utf-8') as f:
    writer = csv.writer(f)
    writer.writerow(['N', 'Wide_Area', 'Narrow_Area', 'Wide_Error_%', 'Narrow_Error_%'])
    for i, N in enumerate(N_values):
        err_wide = abs(estimated_areas_wide[i] - exact_area) / exact_area * 100
        err_narrow = abs(estimated_areas_narrow[i] - exact_area) / exact_area * 100
        writer.writerow([N, estimated_areas_wide[i], estimated_areas_narrow[i], err_wide, err_narrow])


rel_error_wide = [abs(ea - exact_area) / exact_area * 100 for ea in estimated_areas_wide]
rel_error_narrow = [abs(ea - exact_area) / exact_area * 100 for ea in estimated_areas_narrow]

print("график 1")
plt.figure(figsize=(10, 5))
plt.plot(N_values, estimated_areas_wide, label="Широкий прямоугольник", linewidth=1.5, alpha=0.8)
plt.plot(N_values, estimated_areas_narrow, label="Узкий прямоугольник", linewidth=1.5, alpha=0.8)
plt.axhline(y=exact_area, color='r', linestyle='--', linewidth=2, label=f"Точная площадь = {exact_area:.6f}")
plt.xlabel("Количество точек N", fontsize=12)
plt.ylabel("Оценка площади", fontsize=12)
plt.title("Оценка площади методом Монте-Карло", fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig('plot_area3.png', dpi=300)
plt.show()

print("график 2.")
plt.figure(figsize=(10, 5))
plt.plot(N_values, rel_error_wide, label="Широкий прямоугольник", linewidth=1.5, alpha=0.8)
plt.plot(N_values, rel_error_narrow, label="Узкий прямоугольник", linewidth=1.5, alpha=0.8)
plt.xlabel("Количество точек N", fontsize=12)
plt.ylabel("Относительное отклонение (%)", fontsize=12)
plt.title("Относительная ошибка метода Монте-Карло", fontsize=14)
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3)
plt.yscale('log')
plt.tight_layout()
plt.savefig('plot_error3.png', dpi=300)
plt.show()

# g++ -O3 -o monte_carlo_wide.exe monte_carlo_wide.cpp
# g++ -O3 -o monte_carlo_narrow.exe monte_carlo_narrow.cpp
# python data.py