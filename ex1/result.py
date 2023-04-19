#!/usr/bin/env python3
import subprocess
import csv

def main():
    # CSVに結果を出力
    with open('output.csv', mode='w') as csv_file: #上書き
        #表のヘッダー名
        fieldnames = ['memory', 'timeComplexity', 'dist'] 
        writer = csv.DictWriter(csv_file, fieldnames=fieldnames)
        writer.writeheader() #ヘッダー書き込み

        #ファイル番号
        for i in range (0, 100):
            cmd = ["./a.out", str(i)]
            # ./a.out id の結果を取得
            output = subprocess.check_output(cmd)
            print(output.decode())
            memory = int(output.split()[1])
            time_complexity = int(output.split()[3])
            dist = int(output.split()[-1])

            #表のヘッダー名と合わせること
            writer.writerow({'memory': memory, 'timeComplexity': time_complexity, 'dist': dist})



if __name__ == '__main__':
    main()
