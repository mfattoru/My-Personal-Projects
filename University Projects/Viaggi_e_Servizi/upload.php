<?
    function upload(){
	$result = false;
	$immagine = '';
	$size = 0;
	$type = '';
	$nome = '';
	$max_size = 300000;
	$result = is_uploaded_file($_FILES['file']['tmp_name']);
	
	if (!$result){
	    echo "Impossibile eseguire l'upload.";
	    return false;
	}
	else{
	    $size = $_FILES['file']['size'];
	    if ($size > $max_size){
		echo "Il file è troppo grande.";
		return false;
	    }
	    $immagine = file_get_contents($_FILES['file']['tmp_name']);
	    $immagine = addslashes ($immagine);
	    
	    //connect to database
	    include 'dbconnect.php';
	    
	    // make query
	    $sql = "UPDATE Utente SET avatar='".$immagine."' WHERE matricola ='".$_SESSION['matricola']."'";
	    $result = mysql_query ($sql) or die (mysql_error());
	    return true;
	}
    }
?>