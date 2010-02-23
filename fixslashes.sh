if [ $1 ] #Get the directory
then
DIRECTORY=$1
else
echo "FixSlashes: Switch #include statement backslashes
to forwardslashes in all .cpp and .h documents within a tree 
USAGE: $0 <top directory>"
exit
fi

script='if ($_ =~ m/^#include/)
  {
          $_ =~ s/\\/\//g;
  }
  print $_;' #make a perl script

echo $script > temp.pl #save it in a perl file to execute

#Find -o wasn't working properly for some reason
#Run script on all .cpp and .h files
#in the given directory and its subdirectories
find $DIRECTORY -name "*.cpp" -exec perl -ni temp.pl  '{}' \; -print
find $DIRECTORY -name "*.h" -exec perl -ni temp.pl '{}' \; -print

rm temp.pl # remove the script 
