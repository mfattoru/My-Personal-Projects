<!DOCTYPE html>
<html>
    <body>
	<center><top><h2>Seleziona un'immagine per il profilo</h2></top></center>
<?php
    include 'upload.php';
    session_start();
    //check that user is logged in
    if($_SESSION['matricola']){
	if (isset($_FILES['file'])){
	    if(upload()){
	    print("upload completato");
	    }
	}
	echo "
	<h3>Upload</h3>
	<form enctype=\"multipart/form-data\" action=\"".$_SERVER['PHP_SELF']."\" method=\"post\">
	    <input type=\"hidden\" name=\"MAX_FILE_SIZE\" value=\"300000\" />
	    <input type=\"file\" name=\"file\" size=\"40\" />
	    <input type=\"submit\" value=\"Invia\" />
	</form>";
    }
?>
    </body>
</html>