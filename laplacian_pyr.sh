initial_path=./test_files

for lvl in 0 1 2 3 4 5 6 7 8
do
  input_folder_1=${initial_path}/resized_subsamples/g${lvl}
  input_folder_2=${initial_path}/resized_subsamples/g$(expr ${lvl} + 1)
  output_folder=${initial_path}/laplacian/L${lvl}
  mkdir -p $output_folder
  for f_path in ${input_folder_1}/*.png
  do
    input_img_1=${f_path##*/}
    input_img_2=${input_img_1%g?.png}g$(expr ${lvl} + 1).png
    output_img=${input_img_1%g?.png}L${lvl}.png
    ./hw2 -d ${f_path} $input_folder_2/$input_img_2 $output_folder/$output_img
  done
done
