from typing import TextIO

from numpy import array, ndarray


class FileHandler:
    @staticmethod
    def read_matrix(path: str) -> ndarray[ndarray[float]]:
        res = []

        with open(path, mode = 'r', encoding = "utf-8") as f:
            for row in f.readlines():
                res.append(list(map(float, row.split())))
        return array(res)
    
    @staticmethod
    def write_matrices(m1: list[list[float]], m2: list[list[float]],  path: str):
        with open(path, mode = 'w', encoding = "utf-8") as f:
            FileHandler.write_matrix(m1, f)
            f.write('\n')
            FileHandler.write_matrix(m2, f)

    
    @staticmethod
    def write_matrix(m: list[list[float]], file: TextIO):
        for row in m:
            row = list(map(str, row))
            file.write(" ".join(row) + '\n')