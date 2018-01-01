<!--
Java server Page che si occupa della gestione del login dell'utente.la pagina,dopo aver mostrato una form
in cui gli viene richiesto nome utente e password,analizza la presenza dei dati nel database.nel caso in cui 
i dati corrispondano con un utente registrato viene creata una sessione e viene settato l'attributo userid per tenet
traccia della sessione dell'utente
-->
<DOCTYPE html>
<html>
  <head>
    <title>Login</title>
    <%@ page import ="java.sql.*" %>
    <%@ page import ="javax.sql.*" %>
    <%@ page import ="javax.servlet.*" %>
    <%@ page import ="javax.servlet.http.*" %>
  </head>
  
  <body>
    <%
      try{
	if(session.getAttribute("userid")!=null){ //se l'utente  è loggato
	  String redirectURL = "../static/calendario.html";
	  response.sendRedirect(redirectURL);
	}
	else{ //se l'utente non è loggato
	  if(request.getParameter("user") != null && request.getParameter("pwd") != null){ // se ha compilato precedentemente il form per il login
	    int error=1;
	    String userid=request.getParameter("user");
	    String pwd=request.getParameter("pwd"); 
	    //inizializza connessione al database
	    Class.forName("com.mysql.jdbc.Driver"); 
	    java.sql.Connection con = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	    Statement st= con.createStatement(); 
	    //recupera la password del nome utente inserito
	    ResultSet rs=st.executeQuery("select Password from Utente where IdUtente='"+userid+"'"); 
	    if(rs.next()) { //se esiste un utente registrato con quel nome utente confronto le password inserite
	      if(rs.getString(1).equals(pwd)){ //se le password coincidono abilito il flag di creazione sessione
		error=0;
	      } 
	    }  
	    if(error==0){  //credenziali valide
	      //apro la sessione e setto l'attributo userid
	      session=request.getSession(true);  
	      session.setAttribute("userid",userid);
	      //redirigo l'utente alla homepage
	      String redirectURL = "../static/calendario.html";
	      response.sendRedirect(redirectURL);
	    }
	    else{//altrimenti lo redirigo nuovamente alla pagina di login
	      String redirectURL = "../error/login.html";
	      response.sendRedirect(redirectURL);
	    }
	  }
	  else{ //alla prima visualizzazione della pagina mi viene mostrata la form di login che richiede nome utente e password
	    %>
	    
	    <h1 align="center">Login</h1> 

	    <form name="login" id="login" action="../jsp/login.jsp" method="GET" align="center">
	      <!--Utente (lettere, numeri, e i segni . _ -)-->
	      UserName :<input type="text" name="user" required pattern="^([a-zA-Z0-9\.\_\-])+$" title="lettere, numeri, e i segni . _ -"><br>
	      <br>
	      <!--Password (min 6, max 12 di caratteri, numeri, _ * - + ! ? , : ; .e lettere accentate)-->
	      Password :<input type="password" name="pwd" required pattern="^[a-zA-Z0-9\_\*\-\+\!\?\,\:\;\.\xE0\xE8\xE9\xF9\xF2\xEC\x27]{6,12}" title="min 6, max 12 di caratteri, numeri, _ * - + ! ? , : ; .e lettere accentate"><br>
	      <br>
	      <input type="submit" value="Login"/>
	    </form>
	    
	    <%
	  }
	}
      }
      catch(Exception e){
	%>
	impossibile contattare il server riprovare più tardi
	<%
      }
      %>
    </body>

  </head>
</html>