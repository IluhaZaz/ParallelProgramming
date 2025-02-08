import pytest

from subprocess import PIPE, Popen

from numpy import array, allclose

from file_handler import FileHandler

data = [
        ([[1, 2, 3], [4, 5, 6]], [[7, 8], [9, 10], [11, 12]]),
        ([[-1, 0, 3], [4, -5, 6], [1, 1, 1]], [[7, -6, 5], [0, -10, 12], [0, 1, 1]]),
        ([[1.5, 0, 3], [4, -5.6, 6], [1, 1, 1.2]], [[7, -6, 5], [0, -10.4, 12.23], [0.4, 1, 1.3]])
]

@pytest.mark.parametrize("m1, m2", data, ids = ["different_sizes", 
                                                "same_size_and_neg_values", 
                                                "float_values"]
                                                )
def test_matrix_multiply(m1: list[list[float]], m2: list[list[float]]):

    FileHandler.write_matrices(m1, m2, "files\\input.txt")

    prog = Popen("out\\build\\x64-Debug\\main.exe", stdin=PIPE)
    prog.wait()

    res1 = FileHandler.read_matrix("files\\output.txt")

    res2 = array(m1) @ array(m2)

    assert allclose(res1, res2)


data_wrong = [
    ([[1, 2, 3], [4, 5, 6]], [[1, 2, 3], [4, 5, 6]], []),
    ([], [[1, 1, 1], [1, 1, 2]], []),
    ([[1, 2, 3]], [], [])
]

@pytest.mark.parametrize("m1, m2, expected_val", data_wrong, ids = ["incompatible_size", 
                                                                    "first_empty",
                                                                    "second_empty"
                                                                    ]
                                                                    )
def test_matrix_multiply_wrong(m1: list[list[float]], m2: list[list[float]], expected_val: list[list[float]]):
    FileHandler.write_matrices(m1, m2, "files\\input.txt")

    prog = Popen("out\\build\\x64-Debug\\main.exe", stdin=PIPE)
    prog.wait()

    res = FileHandler.read_matrix("files\\output.txt")

    assert res.tolist() == []