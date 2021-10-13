#pragma once
#include <pgmspace.h>

// what to do:
// make get function that runs and gets all saved data from progmem to fill in all fields with it if available 

const char CONFIG_PAGE[] PROGMEM = R"=====(
<html>

<head>
    <meta content="text/html;charset=utf-8" http-equiv="Content-Type">
    <meta content="utf-8" http-equiv="encoding">
    <meta name="viewport" content="width=device-width, initial-scale=1">

</head>
<body>

    <form id='form0'>
        This is a development network, please do not use unless you are permitted access to it.<br><br>
        Set up the configuration:<br>

        AP ssid:<br>
        <input type='text' spellcheck="false" name='AP_SSID' id="AP_SSID" placeholder='ex: bedroom switch'>
        <br>
        Connection SSID:<br>
        <input type='text' spellcheck="false" name='CON_SSID' id="CON_SSID" placeholder='ex: mcdonalds wifi'>
        <br>
        wifi password:<br>
        <input type='password' spellcheck="false" name='CON_PWD' id="CON_PWD" placeholder='ex: password123'>
        <br>
        mqtt ip:<br>
        <input type='text' spellcheck="false" name='MQTT_IP' id="MQTT_IP" placeholder='ex: 10.1.4.22'>
        <br>
        mqtt port:<br>
        <input type='text' spellcheck="false" name='MQTT_PORT' id="MQTT_PORT" placeholder='ex: 1883'>
        <br>
        home assistant discovery configuration:<br>

        <textarea id="MQTT_DISCOVERY" name='DISC' rows='20' cols='80' spellcheck="false" form='form0'></textarea>
        <br>

        <input type='button' name='SUBMIT' value='Submit' onclick="trySubmit()">
    </form>
    <h3 style="display: none;" id="submitOK">Submitted!</h3>
    <h3 style="display: none;" id="submitFailed">JSON Parsing Failed :(</h3>


    <script>
        const form = document.getElementById("form0")
        const submitOk = document.getElementById("submitOK");
        const submitFailed = document.getElementById("submitFailed");

        const ap_ssid = document.getElementById("AP_SSID");
        const con_ssid = document.getElementById("CON_SSID");
        const con_pwd = document.getElementById("CON_PWD");
        const mqtt_port = document.getElementById("MQTT_PORT");
        const mqtt_ip = document.getElementById("MQTT_IP");
        const textbox = document.getElementById("MQTT_DISCOVERY");


        // check if the JSON in the Discovery box is valid
        function checkJSON() { try { JSON.parse(textbox.value); return true; } catch (_) { return false } }

        // Submit the Form
        function trySubmit() {
            if (checkJSON(textbox)) {
                submitOk.style.display = "";
                submitFailed.style.display = "none";
                textbox.style.outlineColor = "";
                textbox.style.outlineStyle = "";


                const data = new URLSearchParams(new FormData(form));
                fetch("/submit", {
                    body: data,
                    method: "POST",
                });
                console.log(data);
                return;
            }
            submitOk.style.display = "none";
            submitFailed.style.display = "";
            textbox.style.outlineColor = "red";
            textbox.style.outlineStyle = "solid";
        }

        // Autofill data from SPIFFs
        async function autofill() {
            // should conform to upper comment
            let parsedData;
            try {
                const data = await fetch("/get");
                parsedData = JSON.parse(await data.text());
            } catch (e) {
                console.error(e);
                // fail and do nothing
                return;
            }

            ap_ssid.value = parsedData.AP_SSID;
            con_ssid.value = parsedData.CON_SSID;
            con_pwd.value = parsedData.CON_PWD;
            mqtt_port.value = parsedData.MQTT_PORT;
            mqtt_ip.value = parsedData.MQTT_IP;

            textbox.value = JSON.stringify(parsedData.DISC, null, 2);

        }

        window.onload = autofill;
    </script>
</body>
</html>
)=====";
