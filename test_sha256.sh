echo "\necho \"pickle rick\" | ./ft_ssl sha256"
echo "pickle rick" | ./ft_ssl sha256
echo "\necho \"Do not pity the dead, Harry.\" | ./ft_ssl sha256 -p"
echo "Do not pity the dead, Harry." | ./ft_ssl sha256 -p
echo "\necho \"Pity the living.\" | ./ft_ssl sha256 -q -r"
echo "Pity the living." | ./ft_ssl sha256 -q -r
echo "\necho \"And above all,\" > file"
echo "And above all," > file
echo "\n./ft_ssl sha256 file"
./ft_ssl sha256 file
echo "\n./ft_ssl sha256 -r file"
./ft_ssl sha256 -r file
echo "\n./ft_ssl sha256 -s \"pity those that aren't following baerista on spotify.\""
./ft_ssl sha256 -s "pity those that aren't following baerista on spotify."
echo "\necho \"be sure to handle edge cases carefully\" | ./ft_ssl sha256 -p file"
echo "be sure to handle edge cases carefully" | ./ft_ssl sha256 -p file
echo "\necho \"some of this will not make sense at first\" | ./ft_ssl sha256 file"
echo "some of this will not make sense at first" | ./ft_ssl sha256 file
echo "\necho \"but eventually you will understand\" | ./ft_ssl sha256 -p -r file"
echo "but eventually you will understand" | ./ft_ssl sha256 -p -r file
echo "\necho \"GL HF let's go\" | ./ft_ssl sha256 -p -s \"foo\" file"
echo "GL HF let's go" | ./ft_ssl sha256 -p -s "foo" file
echo "\necho \"one more thing\" | ./ft_ssl sha256 -r -p -s \"foo\" file -s \"bar\""
echo "one more thing" | ./ft_ssl sha256 -r -p -s "foo" file -s "bar"
echo "\necho \"just to be extra clear\" | ./ft_ssl sha256 -r -q -p -s \"foo\" file"
echo "just to be extra clear" | ./ft_ssl sha256 -r -q -p -s "foo" file
rm file
