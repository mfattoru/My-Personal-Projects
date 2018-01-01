<!--
Java Server Page che si occupa della gestione del luogo di  calcolare il miglior luogo di incontro
tra tutti i partecipanti all'evento.questa pagina riceve in ingresso le mail di tutti i partecipanti necessarie per
recuperare tutti gli indirizzi dei partecipanti da database.quindi tramite la funziona inirialize viene calcolato il miglior luogo di incontro
-->
<!DOCTYPE html>

<html>
  
  <head>
    <title>Scelta Luogo</title>
    <%@ page import= "java.sql.*" %>
    <%@ page import= "javax.sql.*" %>
    <script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBQwyld-63sseJlk5rnF_kPfkKheN3N1jQ&sensor=false"></script>
    <script src="../script/mappaincontro.js" language="JavaScript" type="text/javascript"></script>
    <style type="text/css">
      html { height: 100% }
      body { height: 100%; margin: 0; padding: 0 }
      #map_canvas { height: 100% }
    </style>
    <script> 
      var j=0;
    </script>
  </head>
  
  <body onload="initialize(NumLuoghi)">
    <div id="map_canvas" style="width: 50%; height: 50%;"></div>
    <%
      int i = 1,j=1;
      int FirstNotNull = 0;
      int NumMail=Integer.parseInt(request.getParameter("NumMail")); //recupero del numero di partecipanti selezionati per l'evento
      //inizializzazione della query
      String query ="select Indirizzo from Rubrica where Proprietario='"+session.getAttribute("userid")+"' and ( ";
      String luogo;
      String Email;
      //inizializzazione del link a cui inviare successivamente i dati
      String Link="addevento.jsp?NumMail="+request.getParameter("NumMail")+"&Year="+request.getParameter("Year")+"&Month="+request.getParameter("Month")+"&Day="+request.getParameter("Day")+"&";  
        try{
	  if(session.getAttribute("userid")!=null){
	      //inizializzazione connessione al database
	      Class.forName("com.mysql.jdbc.Driver"); 
	      java.sql.Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	      Statement st= conn.createStatement();
	      ResultSet rs;
	      //recupero indirizzo dell'utente che sta creando l'evento
	      rs=st.executeQuery("select Indirizzo from Utente where IdUtente= '"+session.getAttribute("userid")+"'");
	      rs.next();
	      luogo = rs.getString(1);
		%>
		<input type="hidden" id="0" value="<%=luogo%>" >
		<%
	      while(i <= NumMail){ //se ci sono partecipanti aggiunge la loro mail alla query ed al link
		if( (Email=request.getParameter(Integer.toString(i))) != null){
		  query = query +"Email='" +Email+"'";
		  Link=Link+j+"="+Email;
		  j++;
		}
		i++;
		if(request.getParameter(Integer.toString(i))!=null && j > 1){
		  query = query+" or ";
		  Link=Link+"&";
		}
	      }
	      query = query+" ) ";
	      //se è stata aggiunta almeno una mail alla query,mi recupero gli indirizzi dei partecipanti
	      if(j > 1){
		rs = st.executeQuery(query);
		i = 1;
		while(rs.next()){
		  luogo = rs.getString(1);
	      %>
		  <input type="hidden" id="<%= i%>" value="<%=luogo%>" >
	      <%
		  i++;
		}
	      }
	      else{ //se non inviti nesuno all'evento devo considerare soltanto l'indirizzo del proprietario
		i=1;
	      }
	     %>
	     <script>
	      NumLuoghi=<%=i%>;
	     </script>
	     Indirizzo Consigliato che si riferisce al luogo d'incontro pi&ugrave vicino a tutti i partecipanti,in modo tale da venire in contro alle esigenze di ogni partecipante.
	     se preferisci comunque puoi tranquillamente cambiare il luogo d'incontro ed inserirne uno a tua scelta
	     <form method="POST" action="<%=Link%>">
	     <input type="text" id="Luogo" name="Luogo">
	     <input type="submit" value="Seleziona">
	     </form>
	     <%
	  }
	  else{ //redirect sulla pagina di login nel caso in cui l'utente non sia loggato
	    String redirectURL = "login.jsp";
	    response.sendRedirect(redirectURL);
  	  }
        }catch(Exception e){
	    %>
	      Impossibile effettuare l'operazione
	    <%
        }
    %>
  </body>
  
</html>