package com.eviac.blog.restws;

import java.io.*;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.QueryParam;
import javax.ws.rs.Produces;
import javax.ws.rs.Consumes;
import javax.ws.rs.core.Response;
import javax.servlet.http.HttpServlet;

import org.json.simple.JSONObject;
import org.json.simple.JSONArray;
import org.json.simple.parser.ParseException;
import org.json.simple.parser.JSONParser;


/**
*&nbsp;
* @author Tabor C Henderson
*&nbsp;
*/
@Path("/")
public class Notes extends HttpServlet {
	
	// http responses
	
	// search GET
	@GET
	@Produces("application/json")
	public String userQuery(@QueryParam("query") String query) {
		JSONArray results = new JSONArray();
		results = searchNotes(query);
		//return "You have activated a search for" + query + "\n";
		return results.toString() + "\n";
	}
	
	// retrieval GET
	@GET
	@Path("/{i}")
	@Produces("application/json")
	public String getNote(@PathParam("i") int i) {
		int id = i;
		String nbody = getNoteFromArray(id);
		return nbody + "\n";
	//System.getProperty("user.dir")
	}
	
	// new note POST
	@POST
	@Consumes("application/json")
	// new note POST - new notes get NULL body throws ServletException, IOException
	public Response newPost(InputStream inData) {
		JSONArray JSONnotes = getNotes();
		JSONObject newNote = new JSONObject();
		JSONObject postObj = new JSONObject();
		StringBuilder crunchifyBuilder = new StringBuilder();
		String nBody = "";
		// try to get the POST data
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(inData));
            String line = null;
            while ((line = in.readLine()) != null) {
                crunchifyBuilder.append(line);
            }
            JSONParser parser = new JSONParser();
            // try to parse it
	        try{
	            Object obj = parser.parse(crunchifyBuilder.toString());
	            postObj = (JSONObject)obj;
	            nBody = nBody + postObj.get("body");
	            System.out.println("body in postObj: " + nBody);
	        } catch (ParseException pe){
	           System.out.println("position: " + pe.getPosition());
	           System.out.println(pe);
	        }
        } catch (Exception e) {
            System.out.println("Error Parsing: - ");
        }
 		if (nBody.length() > 1) {
			int count = JSONnotes.size();
			// eventually check for duplicate IDs
			newNote.put("id", count);
			newNote.put("body", nBody);
			JSONnotes.add(newNote);
			// save the JSON object back into notes.txt
			try {
				jsonSave(JSONnotes);
			} catch (IOException e) {};
		} else {
			System.out.println("No note content, not saved.");
		}
        // return HTTP response 200 in case of success
        return Response.status(200).entity(crunchifyBuilder.toString()).build();
	}

	// methods
	
	// build note JSON array from external file - WORKING
	public JSONArray getNotes() {
		JSONArray notesArr = new JSONArray();
		JSONParser parser = new JSONParser();
	        try{
	            Object obj = parser.parse(new FileReader("notes.txt"));
	        	//JSONObject notesObj = (JSONObject) obj;
	            notesArr = (JSONArray)obj;
	        } catch (ParseException pe){
	           System.out.println("position: " + pe.getPosition());
	           System.out.println(pe);
	           //notesObj.put("Error", pe);
	        } catch (IOException e){
		           System.out.println(e);
		           //notesObj.put("Error", pe);
		        }
	        return notesArr;
    }

	// save JSON array into notes.txt - WORKING
	public void jsonSave(JSONArray json) throws IOException {
		PrintWriter file = new PrintWriter("notes.txt");
		file.write(json.toJSONString());
        file.flush();
        file.close();
	}
		
	// grab note by ID from external file - WORKING
	public String getNoteFromArray(int id) {
		JSONArray notesArr = getNotes();
	        String noteString = "";
	        int count = notesArr.size(); // get totalCount of all jsonObjects
	        for(int i=0 ; i< count; i++){   // iterate through jsonArray 
	        	JSONObject jsonNote = (JSONObject) notesArr.get(i);  // get jsonObject @ i position
	        	long noteID = (long) jsonNote.get("id");
	        	String noteBody = (String) jsonNote.get("body");
	        	if (noteID == id) {
	        		noteString = noteBody;
	        	}

		        }
		        return noteString;
	    }

	// search the notes - WORKING
	public JSONArray searchNotes(String q) {
		JSONArray sResults = new JSONArray();
        JSONArray notesArr = getNotes();
            int count = notesArr.size(); // get totalCount of all jsonObjects
	        for(int i=0 ; i< count; i++){   // iterate through jsonArray 
	        	JSONObject jsonNote = (JSONObject) notesArr.get(i);  // get jsonObject @ i position
	        	//long noteID = (long) jsonNote.get("id");
	        	String noteBody = ""+(String) jsonNote.get("body");
	        	Boolean found = noteBody.contains(q);
	        	if (found == true) {
	        		sResults.add(jsonNote);
	        	}

		        }
		        return sResults;
	    }
}