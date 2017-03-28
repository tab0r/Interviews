<?php

header('Content-type: application/json');

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
	$json = file_get_contents('php://input');
	$obj = json_decode($json);
	//var_dump($obj);
	// collect value of input field
	$body = $obj->body;
	if (empty($body)) {
		echo "note is empty, not saved\n";
		} else {
			//echo "New note: ".$body."<br>";
		
			// get new note id
			$newid = count($notes)+1;
			//echo "New note ID: ".$newid."<br>";
			
			// add to notes array for display
			$arr = array("id"=>$newid, "body"=>$body);
			array_push($notesArray, $arr);
		
			// form a string ready to append
			$txt = ','."\n".'{"id" : '.$newid.',"body" : "'.$body.'"}';
			
			// append to notes.txt
			$myfile = fopen("notes.txt", "a") or die("Unable to open file!");
			fwrite($myfile, $txt);
			fclose($myfile);
			
			// echo the saved data
			echo json_encode($arr)."\n";
			};
	} else if ($_SERVER["REQUEST_METHOD"] == "GET") {
		// collect value of input field
		$nid = $_GET['nid'];
		if ($nid==null) {
			echo "Enter a valid note id<br>";
			} else {
			//echo "Recieved note request ".$nid."\n";
			foreach($notesArray as $lid => $note) {
				if ($nid == $lid) {
					echo json_encode($note)."\n";
					//var_dump($note);
					}
			}
			};
		};
	// listing notes
	foreach ($notesArray as $note) {
		//var_dump($note);
		//echo "ID: ".$note['id']." || Body: ".$note['body']."<br>";
		}
?>