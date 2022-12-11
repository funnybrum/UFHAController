const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
 <HEAD>
   <TITLE>Underfloor heating actuator controller</TITLE>
 </HEAD>
 <BODY>
  <form action="/settings" method="get">
   %s<br><br>
   %s<br><br>
   <fieldset style='display: inline-block; width: 300px'>
   <legend>Actuator types</legend>
   %s
   %s
   %s
   %s
   %s
   %s
   %s
   %s
   </fieldset>
   <br><br>
   <input type="submit" value="Save" style='width: 150px;'>
   &nbsp;&nbsp;&nbsp;
   <a href="/reboot">
    <button type="button" style='width: 150px;'>Restart</button>
   </a>
  </form>
 </BODY>
</HTML>
)=====";

const char GET_JSON[] PROGMEM = R"=====({
 "1":%d,
 "2":%d,
 "3":%d,
 "4":%d,
 "5":%d,
 "6":%d,
 "7":%d,
 "8":%d
})=====";