initial_path=./test_files

for lvl in 0 1 2 3 4 5 6 7 8 9
do
  input_folder=${initial_path}/subsamples/g${lvl}
  output_folder=${initial_path}/laplacian/L${lvl}
  mkdir -p $output_folder
  for f_path in ${input_folder}/*.png
  do
    input_img=${f_path##*/}
    #echo ${f%/*.png}
    #echo ${f##*/}
    output_img=${input_img%g?.png}L${lvl}.png
    #echo $f_path
    #echo $output_folder/$output_img
    ./hw2 -d ${f_path} $output_folder/$output_img
  done
done
