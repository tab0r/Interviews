<html>
<body>

<?php
// Aquire and prepare data for whatever

// get the note file contents
$json_string = '{"notes":['.file_get_contents('notes.txt')."]}";
//var_dump($json_string);
	
// convert string to a json object
$notes_jfo = json_decode($json_string) or die("JFO decode failed! <br>");

$notesArray = array();

if (!empty($notes_jfo)) {
	// save notes cell of jfo into array
	$notes = $notes_jfo->notes;
	// translate notes objects into standard arrays
	foreach ($notes as $note) {
		$tID = $note->id;
		$tBody = $note->body;
		$arr = array("id"=>$tID, "body"=>$tBody);
		array_push($notesArray, $arr);
		//echo $note->body."<br>";
		}
}

// handle HTTP request		
if ($_SERVER["REQUEST_METHOD"] == "POST") {
	// collect value of input field
	$body = $_POST['body'];
	if (empty($body)) {
		echo "note is empty, not saved";
		} else {
			echo "New note: ".$body."<br>";
			// note save code goes here
		
			// get new note id
			$newid = count($notes)+1;
			echo "New note ID: ".$newid."<br>";
			
			// add to notes array for display
			$arr = array("id"=>$newid, "body"=>$body);
			array_push($notesArray, $arr);
			echo "<br>";
		
			// form a string ready to append
			$txt = ','."\n".'{"id" : '.$newid.',"body" : "'.$body.'"}';
			// append to notes.txt
			$myfile = fopen("notes.txt", "a") or die("Unable to open file!");
			fwrite($myfile, $txt);
			fclose($myfile);
			};
	} else if ($_SERVER["REQUEST_METHOD"] == "GET") {
		// collect value of input field
		$nid = $_GET['nid'];
		if ($nid==null) {
			echo "Enter a valid note id<br>";
			} else {
			echo "Recieved note request ".$nid."<br>";
			foreach($notesArray as $lid => $note) {
				if ($nid == $lid) {
					echo $note['body'];
					//var_dump($note);
					}
			}
			//echo $notesArray[$nid]['body'];
			};
		};
	//var_dump($notesArray);
	// listing notes
	foreach ($notesArray as $note) {
		//var_dump($note);
		//echo "ID: ".$note['id']." || Body: ".$note['body']."<br>";
		}
		var_dump($_POST);
?>

<div id="id02"></div>

<!-- <script>
notes = <?php //echo "[".file_get_contents('notes.txt');."]" ?>;
displayNotes(notes);
function displayNotes(arr) {
	var out = "";
	var i;
	for(i = 0; i < arr.length; i++) {
		out += arr[i].id + " " +arr[i].body + '<br>';
	}
	out += '<br>' + "Found " + arr.length + " notes.<br>";
	document.getElementById("id02").innerHTML = out;
}
</script>--!>

<form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
  New note: <input type="text" name="body">
  <input type="submit">
</form>

<form method="get" action="<?php echo $_SERVER['PHP_SELF'];?>">
  Get note: <input type="text" name="nid">
  <input type="submit">
</form>
</body>
</html>