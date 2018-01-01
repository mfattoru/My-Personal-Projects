<!--
Java Server Page che si occupa della cancellazione su database di un evento
tramite ID.il quale identificherà univocamente l'evento nel database
-->
<html>

  <head>
    <%@ page import= "java.sql.*" %>
    <%@ page import= "javax.sql.*" %>
    <%@ include file="../WEB-INF/template/sendMail.jsp" %>
  </head>
	
  <body>
  <%
    String Email="";
    String TestoMail;
    String tempMail;
    String NomeEvento="";
    String Mod;
    int flag=1;
    int delete=1;
    
    try{
      if(session.getAttribute("userid")!=null){ //se l'utente è loggato
	Mod=request.getParameter("mod");
	String idevento = request.getParameter("Id");
	//inizializzazione connessione al database
	Class.forName("com.mysql.jdbc.Driver"); 
	java.sql.Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	Statement st= conn.createStatement(); 
	
	ResultSet rs=st.executeQuery("select Nome from Evento where Id='"+idevento+"'");
	if(rs.next()){
	  NomeEvento=rs.getString(1);
	}
	if(Integer.parseInt(Mod)!=75920857){ //se l'evento non è ancora terminato
	  rs=st.executeQuery("select Email from PartecipaEvento where IdEvento= '"+idevento+"'");
	  while(rs.next()){

	    flag=0;
	    tempMail=rs.getString(1)+",";
	    Email=Email+tempMail;
	  }
	  if(flag==0){ //se c'è almeno un partecipante,informali della modifica dell'evento
	    TestoMail="Gentile utente la avvertiamo che l'evento "+NomeEvento+" a cui lei stava partecipando e' stato annullato";  
	    if(sendMail(Email,"Evento Annullato",TestoMail)){  
	      delete=0; //flag per permettere di cancellare l'evento
	      %>
	      <center>
	      <p>&egrave stata inviata una mail a tutti i partecipandi per avvisarli  che l'evento &egrave stato annullato</p>
	      </center>
	      <%
	    }
	    else{
	      %>
	      <center>
		<p>Purtroppo non siamo riusciti ad inviare una mail per avvisare tutti i partecipanti dell'annullameno dell'evento,riprova pi&ugrave tardi</p>
	      </center>
	      <%
	    }
	  }
	}
	//cancellazione avento dal database
	if(delete==0){
	  st.executeUpdate("delete from Evento where Id='"+idevento+"'");
	  %>
	    <center>
	      <p>Cancellazione dell'evento avvenuta correttamente.</p>
	    </center>
	  <%
	}
	%>
	<META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../static/calendario.html">
	<%
      }
      else{ //redirezione in caso di utente non loggato
	String redirectURL = "login.jsp";
	response.sendRedirect(redirectURL);
      }
    }
    catch(Exception e){
    %>
      <p align="center">errore durante la cancellazione </p>
    <%
    }
  %>
  </body>

</html>