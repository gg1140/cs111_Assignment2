initial_path=./test_files

for lvl in 0 1 2 3 4 5 6 7 8 9
do
  input_folder=${initial_path}/subsamples/g${lvl}
  output_folder=${initial_path}/resized_subsamples/g${lvl}
  mkdir -p $output_folder
  for f_path in ${input_folder}/*.png
  do
    input_img=${f_path##*/}
    output_img=${input_img%g?.png}g${lvl}.png
    ./hw2 --resize ${f_path} 512 512 $output_folder/$output_img
  done
done
