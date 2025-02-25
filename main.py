import numpy as np
import matplotlib.pyplot as plt

from subprocess import PIPE, Popen

from numpy import array, allclose

from file_handler import FileHandler

EXPEREMENT_COUNT = 10

times = []
sizes = [i*300 for i in range(1, 11)]

for matr_size in sizes:
    time = 0
    for _ in range(EXPEREMENT_COUNT):
        m1 = np.random.rand(matr_size, matr_size)
        m2 = np.random.rand(matr_size, matr_size)

        FileHandler.write_input_file(m1, m2, "files\\input.txt")
        prog = Popen("out\\build\\x64-Debug\\main.exe", stdin=PIPE)
        prog.wait()

        res1, t = FileHandler.read_output_file("files\\output.txt")
        time += float(t)

        res2 = array(m1) @ array(m2)

        if not allclose(res1, res2):
            raise ValueError("Wrong answer")
    times.append(time/EXPEREMENT_COUNT)
    print(f"{matr_size}: {times}")


plt.plot(sizes, times)
plt.title('Зависимость времени умножения матриц от их размеров')
plt.xlabel('Размер квадратной матрицы')
plt.ylabel('Время умножения, с')
plt.show()