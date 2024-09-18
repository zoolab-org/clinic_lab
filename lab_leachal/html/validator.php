<?php
	header("Content-Type: application/json");

	if(isset($_GET['msg']) == FALSE || isset($_GET['hash']) == FALSE) {
		echo json_encode(array( "status" => "ERR", "msg" => "<none>",
				"hash" => "<none>", "detail" => "Missing argument(s)." ));
		die;
	}

	$msg = $_GET['msg'];
	if(($bmsg = base64_decode($msg, TRUE)) === FALSE) {
		echo json_encode(array( "status" => "ERR", "msg" => "<none>",
				"hash" => "<none>", "detail" => "Invalid BASE64 input." ));
		die;
	}

	$hash = $_GET['hash'];
	$secret = file_get_contents("/SECRET");
	$check = sha1($secret . $bmsg);

	if($check === $hash) {
		if($msg === "Hello, World!") {
			echo json_encode(array( "status" => "OK", "msg" => $msg,
					"hash" => $hash, "detail" => "Validation passed (Sample!)." ));
		} else {
			echo json_encode(array( "status" => "OK", "msg" => $msg,
					"hash" => $hash, "detail" => "Validation passed." ));
		}
	} else {
		echo json_encode(array( "status" => "ERR", "msg" => $msg,
				"hash" => $hash, "detail" => "Validation failed." ));
	}
