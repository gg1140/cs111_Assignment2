initial_path=./test_files/subsamples

for lvl in 0 1 2 3 4 5 6 7 8
do
  input_folder=${initial_path}/g${lvl}
  output_folder=${initial_path}/g$(expr ${lvl} + 1)
  mkdir -p $output_folder
  for f_path in ${input_folder}/*
  do
    input_file=${f_path##*/}
    output_file=${input_file%g?.png}g$(expr ${lvl} + 1).png
    #echo ${f%/*.png}
    #echo ${f##*/}
    ./hw2 -gr ${f_path} ${output_folder}/${output_file}
  done
done
