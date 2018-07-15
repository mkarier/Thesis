$prefix = "../../";
$folderToProc = "ScannedAlphabet";
$folderToContour = "Alphabet";

for($fileNumber = 1; $fileNumber <= 52; $fileNumber = $fileNumber + 1)
{
	system("./CleanImage $prefix$folderToProc/scan1-$fileNumber.jpeg $prefix$folderToContour/ 52 &");
	system("./ShowContour $prefix$folderToContour/scan1-$fileNumber.png $prefix$folderToContour/ 52");
}