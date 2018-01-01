<html>

    <head>
      <title>Index</title>
    </head>
    <body>
    <%
    if(session.getAttribute("userid")==null){
    %>
	<H1 align="center"> Agenda 2012 </H1>
	<p align="center">
	<br><br>
	<a href="static/registrazione.html">Registrazione</a>
	<br><br>
	<a href="jsp/login.jsp">LogIn</a>
	<br><br>
	<a href="jsp/recuperapwd.jsp"> Recupero password</a>
     </p>
     <%
     }
     else{

	String redirectURL = "static/calendario.html";
        response.sendRedirect(redirectURL);
      }
     %>
    </body>

</html>
