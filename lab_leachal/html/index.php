<html>
<head>
<meta charset="utf-8"/>
<style>
body {
	font-family: monospace;
	width: 60%;
	margin: 1em;
}
body > div { margin-left: 20%; }
body > div > div { margin: 1em 0; }
form > div { padding: 1ex 1ex; }
input { font-family: monospace; }
</style>
<script type="text/javascript" src="validator.js"></script>
</head>
<body>
<div id="main">

	<h1>Secret Validation Service</h1>

	<div><p>Send me a message to prove that you know the hidden secret :)</p></div>

	<div>
	<form method="GET">
	<div>Message: <input id="msg" name="msg" type="text" size="24"/> (base64 encoded string)</div>
	<div>Hashval: <input id="hash" name="hash" type="text" size="24"/>
		 <input id="validator" type="button" value="Validate"/></div>
	<div>
	<p>One sample (message, hash-value) pair is available here:</p>
	<ul>
<?php
	$secret = file_get_contents("/SECRET");
	$msg = "Hello, World!";
	$hash = sha1($secret . $msg);
	$bmsg = base64_encode($msg);
	echo "<li>Message: [$bmsg]</li>\n";
	echo "<li>Hashval: [$hash] (SHA1)</li>\n";
?>
	</ul>
	<p>Try it by yourself!</p>
	</div>

	</form>
	</div>

	<hr/>

	<div>
	<h2>Validation Result</h2>
	<p>Message: <span id="result_msg"></span></p>
	<p>Hashval: <span id="result_hash"></span></p>
	<p>_Result: <span id="result_desc"></span></p>
	</div>

	<hr/>

	<code id="code"><?php
	show_source("./validator.php");
	?></code>

</div>
</body>
</html>
