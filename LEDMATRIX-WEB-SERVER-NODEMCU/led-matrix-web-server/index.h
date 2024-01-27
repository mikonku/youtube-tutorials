const char page[] PROGMEM = R"=====(


<!DOCTYPE html>
<html>
  <body>

    <h2>Led Matrix</h2>
    <form action="/">
    	<label for="animation">Animasi:</label><br>
      <select name="animation" id="animation">
        <option value="0">PA_SCROLL_LEFT</option>
        <option value="1">PA_SCROLL_RIGHT</option>
       
      </select>
      <br>
      <br>
      <label for="text">Text:</label><br>
      <input type="text" id="text" name="text">
      <br>
      <br>
      <input type="submit" value="Submit">
    </form> 

  </body>
</html>


)=====";