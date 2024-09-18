"use strict"

function run_validator() {
	var msg = document.getElementById('msg').value;
	var hash = document.getElementById('hash').value;
	const req = new XMLHttpRequest();

	req.onreadystatechange = function() {
		if(req.readyState === XMLHttpRequest.DONE && req.status == 200) {
			const obj = JSON.parse(req.responseText);
			var rmesg = document.getElementById('result_msg');
			var rhash = document.getElementById('result_hash');
			var rdesc = document.getElementById('result_desc');

			console.log(obj);
			rmesg.textContent = atob(obj['msg']).toString();
			rhash.textContent = obj['hash'];
			rdesc.textContent = obj['detail'];

			if(obj['status'] == "OK") {
				rdesc.style.color = "#0000ff";
			} else {
				rdesc.style.color = "#ff0000";
			}
		}
	};

	req.open("GET", window.location.origin + "/validator.php?msg=" + encodeURIComponent(msg) + "&hash=" + encodeURIComponent(hash));
	req.send();
}

document.addEventListener('DOMContentLoaded', function() {
	var validator = document.getElementById('validator');
	validator.addEventListener('click', run_validator);
});
