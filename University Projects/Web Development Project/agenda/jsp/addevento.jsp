<!--
Java Server page per la gestione dell'aggiunta di nuovi eventi
-->
<html>
  <head>
    <title>Aggiungi Evento</title>
    <%@ page import= "java.sql.*" %>
    <%@ page import= "javax.sql.*" %>
    <%@ include file="../WEB-INF/template/sendMail.jsp" %>
    
    <SCRIPT type="text/javascript" SRC="../script/checkOra.js"></SCRIPT>
  </head>
  <body>
    <% 
      try{
	int i=1;
	int max= Integer.parseInt(request.getParameter("NumMail"));
	String mail="";
	String temp="";
	if(session.getAttribute("userid")!=null){  //se l'utente è loggato
	    String Luogo = request.getParameter("Luogo");
	    if(request.getParameter("Data")!=null){  //se l'utente ha precedentemente compilato correttamente tutti i campi della form 
	      String Prop = (String)session.getAttribute("userid");
	      String Nome = request.getParameter("NomeEvento");
	      String Data = request.getParameter("Data");
	      String OraInizio = request.getParameter("OraInizio");
	      String OraFine = request.getParameter("OraFine");
	      String Descr = request.getParameter("Descrizione");
	      String Email= request.getParameter("Partecipanti");
	      Class.forName("com.mysql.jdbc.Driver");
	      //connessione al database
	      java.sql.Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/Agenda","AdminAgenda","Agenda123"); 
	      Statement st= conn.createStatement();
	      //inserimento del nuovo evento nel database
	      st.executeUpdate("insert into Evento(Nome,OraInizio,OraFine,Data,Descrizione,Luogo,Proprietario) values ('"+Nome+"','"+OraInizio+"','"+OraFine+"','"+Data+"','"+Descr+"','"+Luogo+"','"+Prop+"')");
	      //recupero dell'id dell'evento appena creato,necessario per la creazione dell'URL per permettere agli utenti invitati dall'utente di partecipare
	      ResultSet rs=st.executeQuery("select Id from Evento where Nome='"+Nome+"' and OraInizio='"+OraInizio+"' and OraFine='"+OraFine+"' and Data='"+Data+"' and Descrizione='"+Descr+"' and Luogo='"+Luogo+"'and Proprietario='"+Prop+"'");
	      rs.next();
	      String Evento=rs.getString("Id");
	      //invio della mail a tutti gli invitati selezionati precedentemente
	      if(sendMail(Email,"Evento","http://127.0.0.1:8080/agenda/jsp/partecipaevento.jsp?Id="+Evento)){ 
		%>
		<p align="center">evento inserito correttamente</p>
		<p align="center">&egrave stata mandata una mail a tutti i partecipanti</p>
		<META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../static/calendario.html">
		<%
	      }
	      else{
	      %>
		<p align="center">evento inserito correttamente</p>
		<p align="center">abbiamo riscontrato un problema durante l'invio delle mail,si prega di riprovare più tardi</p>
		<META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../static/calendario.html">
	      <%
	      }
	    }
	    else{  //form da compilare per la creazione dell'evento
	      //recupero dati dalla richiesta
	      String Anno=request.getParameter("Year");
	      String Mese=request.getParameter("Month");
	      String Giorno=request.getParameter("Day");
	      String NumMail=request.getParameter("NumMail");  //numero di partecipanti selezionati precedentemente
	      while(i<=max){
		if(request.getParameter(Integer.toString(i))!=null){ //recupero delle mail dei partecipanti
		  mail+=request.getParameter(Integer.toString(i))+",";
		  temp+=request.getParameter(Integer.toString(i))+", ";
		}
		i++;
	      }
	      %>
	      <center>
		<form name="checkOra" id="checkOra" method="GET" action="addevento.jsp" onSubmit="return controllo();"> 
		  <!--NomeEvento (caratteri,numeri, lettere accentate apostrofo e un solo spazio fra le parole)-->
		  Nome Evento:<input type="text" name="NomeEvento" required pattern="^([a-zA-Z0-9\xE0\xE8\xE9\xF9\xF2\xEC\x27]\s?)+$" title="caratteri,numeri, lettere accentate apostrofo e un solo spazio fra le parole"><br>
		  <input type="hidden" name="Data" value="<%=Anno%>-<%=Mese%>-<%=Giorno%>">
		  <input type="hidden" name="NumMail" value="<%=NumMail%>">
		  <!--ora (accetta ore tra 0 e 24 con una o 2 cifre, minuti e secondi da 0 a 60 con una o due cifre e come separatore :)-->
		  Ora Inzio:<input type="text" name="OraInizio" required pattern="^(([0-1]?[0-9])|(2[0-4]))((:)[0-6]?[0-9])+$" title="accetta ore tra 0 e 24 con una o 2 cifre, minuti e secondi da 0 a 60 con una o due cifre e come separatore :"><br>
		  Ora Fine:<input type="text" name="OraFine" required pattern="^(([0-1]?[0-9])|(2[0-4]))((:)[0-6]?[0-9])+$" title="accetta ore tra 0 e 24 con una o 2 cifre, minuti e secondi da 0 a 60 con una o due cifre e come separatore :"><br>
		  <!--Luogo,(caratteri,numeri,virgola ,lettere accentate ,apostrofo e un solo spazio fra le parole)-->
		  Luogo:<input type="text" name="Luogo" value="<%=Luogo%>" required pattern="^([a-zA-Z0-9\ \xE0\xE8\xE9\xF9\xF2\xEC\x27,])+$" title="caratteri,numeri,virgola lettere accentate apostrofo e un solo spazio fra le parole"><br>
		  Descrizione:<input type="text" name="Descrizione"><br>
		  Partecipanti:
		  <table border=1>
		    <td>
		      <div style="width:300px; height:100px; overflow:scroll;">
			<%=temp%>
		      </div>
		    </td>
		  </table>
		  <input type="hidden" name="Partecipanti" value="<%=mail%>"><br>
		  <input type="submit" value="Aggiungi Evento">
		  <input type="reset" value="Cancella campi">
		</form>
	      </center>
	      <%
	    }
	}
	else{  //redirezione alla pagina di login in caso l'utente non sia loggato
	  String redirectURL = "login.jsp";
	  response.sendRedirect(redirectURL);
	}
      }
      catch(Exception e){
      %>
	<p align="center">errore durante l'inserimento</p>
	<META HTTP-EQUIV="REFRESH" CONTENT="5; URL=../static/calendario.html">
      <%
      }
    %>
  </body>

</html>