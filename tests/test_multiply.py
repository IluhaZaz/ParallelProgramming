from subprocess import PIPE, Popen

from numpy import array, allclose

from file_handler import FileHandler


def test_1():
    m1 = [
        [1, 2, 3],
        [4, 5, 6]
    ]

    m2 = [
        [7, 8],
        [9, 10],
        [11, 12]
    ]

    FileHandler.write_matrices(m1, m2, "files\\input.txt")

    prog = Popen("out\\build\\x64-Debug\\main.exe", stdin=PIPE)
    prog.wait()

    res1 = FileHandler.read_matrix("files\\output.txt")

    res2 = array(m1) @ array(m2)

    assert allclose(res1, res2)


def test_2():
    m1 = [
        [-1, 0, 3],
        [4, -5, 6],
        [1, 1, 1]
    ]

    m2 = [
        [7, -6, 5],
        [0, -10, 12],
        [0, 1, 1]
    ]

    FileHandler.write_matrices(m1, m2, "files\\input.txt")

    prog = Popen("out\\build\\x64-Debug\\main.exe", stdin=PIPE)
    prog.wait()

    res1 = FileHandler.read_matrix("files\\output.txt")

    res2 = array(m1) @ array(m2)

    assert allclose(res1, res2)


def test_3():
    m1 = [
        [1.5, 0, 3],
        [4, -5.6, 6],
        [1, 1, 1.2]
    ]

    m2 = [
        [7, -6, 5],
        [0, -10.4, 12.23],
        [0.4, 1, 1.3]
    ]

    FileHandler.write_matrices(m1, m2, "files\\input.txt")

    prog = Popen("out\\build\\x64-Debug\\main.exe", stdin=PIPE)
    prog.wait()

    res1 = FileHandler.read_matrix("files\\output.txt")

    res2 = array(m1) @ array(m2)

    assert allclose(res1, res2)