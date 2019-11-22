# Embed2img
embed secret information to image

### src

dependency: opencv 3.1

### dist

If want to run it simply, you can directly run `Embed2Img.exe`. 

> usage:
>
> WARNING: \${} can be repalced, but file type don't change.
>
> encrpt:
> ​        -e \${input_file_name}.bmp \${mask_file_name}.bmp \${output_file_name}.png
>
> decrypt:
> ​        -d \${secret_file_name}.png ${mask_file_name}.png

**NOTE：**

This executable file should be run in command. Don't double click it! Only proper parameters can run it.