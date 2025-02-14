from typing import TextIO

from numpy import array, ndarray


class FileHandler:
    @staticmethod
    def read_output_file(path: str) -> list:

        with open(path, mode = 'r', encoding = "utf-8") as f:
            res = FileHandler.read_matrix(f)

            time: int = f.readline()
        return array(res), time
    
    @staticmethod
    def read_matrix(file: TextIO) -> ndarray[ndarray[float]]:
        res = []

        row = file.readline()
        while row != "\n":
            res.append(list(map(float, row.split())))
            row = file.readline()
        return array(res)
    
    @staticmethod
    def write_input_file(m1: list[list[float]], m2: list[list[float]],  path: str):
        with open(path, mode = 'w', encoding = "utf-8") as f:
            FileHandler.write_matrix(m1, f)
            f.write('\n')
            FileHandler.write_matrix(m2, f)

    
    @staticmethod
    def write_matrix(m: list[list[float]], file: TextIO):
        for row in m:
            row = list(map(str, row))
            file.write(" ".join(row) + '\n')