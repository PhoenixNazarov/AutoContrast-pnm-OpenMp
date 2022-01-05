import threading
import subprocess
import os
import time
from shutil import copyfile
import random
import json

inp_path = "test//input//"
name_file_glob = 'picTest8.ppm'
out_path = "test//output//"
incorrect_path = 'test/incorrect/'

cf = 0.1


# too slow
def tests_parallel(threads, runs):
    end_threads = [0]
    out = {
        "min-max": 0,
        "change_col": 0,
        "sum": 0
    }

    def open_hw():
        exe_file = str(random.random())[2:]
        _inp_path = inp_path + exe_file
        _out_path = out_path + exe_file
        copyfile('hw5.exe', exe_file + '.exe')
        copyfile(inp_path + name_file_glob, _inp_path)
        cmd = f"{exe_file + '.exe'} {threads} {_inp_path} {_out_path} {cf}"
        res = subprocess.getoutput(cmd).split("\n")
        os.remove(_out_path)
        os.remove(_inp_path)
        os.remove(exe_file + '.exe')
        # find min-max  2208
        # change_colors 467
        # Time (0 thread(s)): 2760 ms
        out["min-max"] += float(res[0].removeprefix('find min-max  '))
        out["change_col"] += float(res[1].removeprefix('change_colors '))
        out["sum"] += int(res[2][res[2].find(': ') + 2:res[2].find(' ms')])
        end_threads[0] += 1

    for i in range(runs):
        threading.Thread(target=open_hw).start()
    a = time.time()
    while end_threads[0] != runs:
        pass
    print(time.time() - a)
    for i in out:
        out[i] /= runs
        out[i] = round(out[i])

    return out


def tests_sequence(threads, runs, name_file=name_file_glob):
    out = {
        "min-max": 0,
        "change_col": 0,
        "sum": 0
    }

    def open_hw():
        exe_file = 'hw5.exe'
        _inp_path = inp_path + name_file
        _out_path = out_path + name_file
        cmd = f"{exe_file} {threads} {_inp_path} {_out_path} {cf}"
        res = subprocess.getoutput(cmd).split("\n")
        print(res)
        # find min-max  2208
        # change_colors 467
        # Time (0 thread(s)): 2760 ms
        # out["min-max"] += float(res[0].removeprefix('find min-max  '))
        # out["change_col"] += float(res[1].removeprefix('change_colors '))
        out["sum"] += int(res[0][res[0].find(': ') + 2:res[0].find(' ms')])

    for i in range(runs):
        try:
            open_hw()
        except Exception as e:
            pass

    for i in out:
        out[i] /= runs
        out[i] = round(out[i])

    return out



imgs = os.listdir(inp_path)
for i in imgs:
    tests_sequence(1, 1, i)

# test incorrect
# inp_path = incorrect_path
# imgs = os.listdir(incorrect_path)
# for i in imgs:
#     tests_sequence(1, 1, i)

# check_threads = [i for i in range(21)]
# check_threads += [30, 40, 50, 64, 128, 256]
# check_threads = [0, 1, 4, 8, 10, 16, 20, 40, 50, 100, 128, 256]
# median = 5
# a = {}
# b = []
# with open('test_output.txt', 'w') as file:
#     for i in check_threads:
#         res = tests_sequence(i, median)
#         a.update({i:res})
#         b.append(res['sum'])
#         print(f"RESULT FOR {i} threads")
#         print(f"RESULT FOR {i} threads", file=file)
#         print(res, res['sum'] - res["min-max"] - res["change_col"])
#         print(res, file=file)
#         print()
#         print('', file=file)
#     print(json.dumps(a), file=file)
#     print(json.dumps(b), file=file)
#     print(b)
