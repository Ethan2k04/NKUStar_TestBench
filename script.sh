#!/bin/bash

function waiting()
{
    i=0
    while [ $i -le 10 ]
    do
        for j in '\\' '|' '/' '-'
        do
            printf "%c%c%c%c%c test waiting %c%c%c%c%c\r" \
            "$j" "$j" "$j" "$j" "$j" "$j" "$j" "$j" "$j" "$j"
            sleep 0.1
        done
        let i=i+4
    done
    echo
}

cpp_files=("./src/GaussianFilter.cpp" "./src/FFT.cpp" "./src/MonteCarloIntegration.cpp" "./src/Alpha-Beta.cpp" "./src/Matrix.cpp" "./src/RandomReadWrite.cpp" "./src/OrderReadWrite.cpp" "./src/AStar.cpp" "./src/Subsets.cpp")

for cpp_file in "${cpp_files[@]}"; do
  executable_name="${cpp_file%.cpp}"

  if [ ! -f "$executable_name" ]; then
    g++ -o "./obj/$(basename "$executable_name")" $cpp_file
    if [ $? -eq 0 ]; then
      echo "Compilation of $cpp_file was successful"
    else
      echo "Compilation of $cpp_file failed"
    fi
  fi
done
clear

echo " _   _ _  ___   _ ____  _             "
echo "| \ | | |/ / | | / ___|| |_ __ _ _ __ "
echo "|  \| | ' /| | | \___ \| __/ _\ | ___|"
echo "| |\  | . \| |_| |___) | || (_| | |   "
echo "|_| \_|_|\_\\___/|____/ \__\__,_|_|   "

declare -A benchmark_scores

while true; do
  echo "====== CPU Benchmark 测试 ======"
  echo "1. GaussianFilter"
  echo "2. FFT"
  echo "3. MonteCarloIntegration"
  echo "4. Alpha-Beta Pruning"
  echo "5. Matrix Operations"
  echo "6. Random Read Write Files"
  echo "7. Order Read Write Files"
  echo "8. A-Star Path Finding"
  echo "9. Subsets Counting"
  echo "0. 测试全部"
  echo "-1. 退出"
  read -p "请选择测试项目: " choice

  case $choice in
    1)
      echo "====== GaussianFilter 测试 ======"
      waiting 
      score=$(./obj/GaussianFilter) 
      echo "GaussianFilter score: $score"
      benchmark_scores["GaussianFilter"]=$score
      ;;
    2)
      echo "====== FFT 测试 ======"
      waiting
      score=$(./obj/FFT)
      echo "FFT score: $score"
      benchmark_scores["FFT"]=$score
      ;;
    3)
      echo "====== MonteCarloIntegration 测试 ======"
      waiting
      score=$(./obj/MonteCarloIntegration)
      echo "MonteCarloIntegration score: $score"
      benchmark_scores["MonteCarloIntegration"]=$score
      ;;
    4)
      echo "====== Alpha-Beta Pruning 测试 ======"
      waiting
      score=$(./obj/Alpha-Beta)
      echo "Alpha-Beta Pruning score: $score"
      benchmark_scores["Alpha-Beta Pruning"]=$score
      ;;
    5)
      echo "====== Matrix Operations 测试 ======"
      waiting
      score=$(./obj/Matrix)
      echo "Matrix Operations score: $score"
      benchmark_scores["Matrix Operations"]=$score
      ;;
    6)
      echo "====== Random Read Write Files 测试 ======"
      waiting
      score=$(./obj/RandomReadWrite)
      echo "$score"
      benchmark_scores["RandomReadWrite"]=$score
      ;;
    7)
      echo "====== Order Read Write Files 测试 ======"
      waiting
      score=$(./obj/OrderReadWrite)
      echo "$score"
      benchmark_scores["OrderReadWrite"]=$score
      ;;
    8)
      echo "====== A-Star Path Finding 测试 ======"
      waiting
      score=$(./obj/AStar)
      echo "A-Star Path Finding score: $score"
      benchmark_scores["AStar"]=$score
      ;;
    9)
      echo "====== Subsets Counting 测试 ======"
      waiting
      score=$(./obj/Subsets)
      echo "Subsets Counting score: $score"
      benchmark_scores["Subsets"]=$score
      ;;
    0)
      echo "====== 测试进行中 ======"
      waiting
      score=$(./obj/GaussianFilter)
      benchmark_scores["GaussianFilter"]=$score
      score=$(./obj/FFT)
      benchmark_scores["FFT"]=$score
      score=$(./obj/MonteCarloIntegration)
      benchmark_scores["MonteCarloIntegration"]=$score
      score=$(./obj/Alpha-Beta)
      benchmark_scores["Alpha-Beta Pruning"]=$score
      score=$(./obj/Matrix)
      benchmark_scores["Matrix Operations"]=$score
      score=$(./obj/RandomReadWrite)
      benchmark_scores["RandomReadWrite"]=$score
      score=$(./obj/OrderReadWrite)
      benchmark_scores["OrderReadWrite"]=$score
      score=$(./obj/AStar)
      benchmark_scores["AStar"]=$score
      score=$(./obj/Subsets)
      benchmark_scores["Subsets"]=$score
      echo "====== 测试结果 ======"
      for key in "${!benchmark_scores[@]}"; do
        echo "$key: ${benchmark_scores[$key]}"
      done
      break
      ;;
    -1)
      clear
      echo "====== 测试结果 ======"
      for key in "${!benchmark_scores[@]}"; do
        echo "$key: ${benchmark_scores[$key]}"
      done
      break
      ;;
    *)
      echo "无效的选择"
      ;;
  esac

  read -p "按任意键继续..."
done