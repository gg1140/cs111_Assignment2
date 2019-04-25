initial_path=./test_files

for lvl in 0 1 2 3 4 5 6 7 8
do
  input_folder=${initial_path}/subsamples/g${lvl}
  output_folder=${initial_path}/subsamples/g$(expr ${lvl} + 1)
  mkdir -p $output_folder
  for f_path in ${input_folder}/*.png
  do
    input_img=${f_path##*/}
    #echo ${f%/*.png}
    #echo ${f##*/}
    output_img=${input_img%g?.png}g$(expr ${lvl} + 1).png
    #echo $f_path
    #echo $output_folder/$output_img
    ./hw2 -gr ${f_path} $output_folder/$output_img
  done
done
