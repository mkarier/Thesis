$maxFiles = 207;
$folder = "ImageDatabase";
$fileType = "png";
$resultsPath = "../../Results/test";

for($fileNumber = 32; $fileNumber <= $maxFiles; $fileNumber = $fileNumber + 1)
{
	print "fileNumber $fileNumber\n";
	system("./CleanImage ../../$folder/scan1-$fileNumber.$fileType ../../$folder/  $maxFiles");
}
