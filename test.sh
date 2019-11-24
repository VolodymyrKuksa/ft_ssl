ALGO=$1

echo "\necho \"pickle rick\" | ./ft_ssl $ALGO"
echo "pickle rick" | ./ft_ssl $ALGO
echo "\necho \"Do not pity the dead, Harry.\" | ./ft_ssl $ALGO -p"
echo "Do not pity the dead, Harry." | ./ft_ssl $ALGO -p
echo "\necho \"Pity the living.\" | ./ft_ssl $ALGO -q -r"
echo "Pity the living." | ./ft_ssl $ALGO -q -r
echo "\necho \"And above all,\" > file"
echo "And above all," > file
echo "\n./ft_ssl $ALGO file"
./ft_ssl $ALGO file
echo "\n./ft_ssl $ALGO -r file"
./ft_ssl $ALGO -r file
echo "\n./ft_ssl $ALGO -s \"pity those that aren't following baerista on spotify.\""
./ft_ssl $ALGO -s "pity those that aren't following baerista on spotify."
echo "\necho \"be sure to handle edge cases carefully\" | ./ft_ssl $ALGO -p file"
echo "be sure to handle edge cases carefully" | ./ft_ssl $ALGO -p file
echo "\necho \"some of this will not make sense at first\" | ./ft_ssl $ALGO file"
echo "some of this will not make sense at first" | ./ft_ssl $ALGO file
echo "\necho \"but eventually you will understand\" | ./ft_ssl $ALGO -p -r file"
echo "but eventually you will understand" | ./ft_ssl $ALGO -p -r file
echo "\necho \"GL HF let's go\" | ./ft_ssl $ALGO -p -s \"foo\" file"
echo "GL HF let's go" | ./ft_ssl $ALGO -p -s "foo" file
echo "\necho \"one more thing\" | ./ft_ssl $ALGO -r -p -s \"foo\" file -s \"bar\""
echo "one more thing" | ./ft_ssl $ALGO -r -p -s "foo" file -s "bar"
echo "\necho \"just to be extra clear\" | ./ft_ssl $ALGO -r -q -p -s \"foo\" file"
echo "just to be extra clear" | ./ft_ssl $ALGO -r -q -p -s "foo" file
rm file
