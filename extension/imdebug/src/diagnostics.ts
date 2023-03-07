import * as vscode from 'vscode';
import fetch from 'node-fetch';

const API_URL = 'http://localhost:8080/';

type DiagnosticItem = {
    // eslint-disable-next-line @typescript-eslint/naming-convention
    line_index: number;
    text: string;
    severity: vscode.DiagnosticSeverity;
};

type Model = {
    label: string;
    detail: string;
}

export function getModels(): Promise<Array<Model>> {
    return fetch(API_URL.concat('get_model_names'), {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
          }
    }).then(response => {
        if (!response.ok) {
          throw new Error(response.statusText);
        }
        return response.json();
      });
}



function readDocumentProbs(doc: vscode.TextDocument, modelName: String) : Promise<Array<DiagnosticItem>> {

    return fetch(API_URL.concat('analyze_code'), {
        method: "POST",
        headers: {
            // eslint-disable-next-line @typescript-eslint/naming-convention
            "Content-Type": "application/json",
          },
        body: JSON.stringify({
            code: doc.getText(),
            file_name: doc.fileName,
            model_name: modelName,
        })
    }).then(response => {
        if (!response.ok) {
          throw new Error(response.statusText);
        }
        return response.json();
      });
}

function refreshDiagnostics(doc: vscode.TextDocument, diagnosticsCollection: vscode.DiagnosticCollection, modelName: String = 'LineVul'): void {
    vscode.window.withProgress(
        { location: vscode.ProgressLocation.Notification, title: "IMDBug: working on file" },
        async (_) => {
            console.log("Refreshing diagnostics for file with model: %s", modelName)
            
            const diagnostics: vscode.Diagnostic[] = [];
            const items = await readDocumentProbs(doc, modelName).catch((e) =>{ console.log("Got error from server: %s", e); return []});
            for (let i = 0; i < items.length; i++) {
                const diagnostic = createDiagnostic(items[i], doc);
                if (diagnostic) {
                    diagnostics.push(diagnostic);
                }
            }
            diagnosticsCollection.set(doc.uri, diagnostics);
        },
    );

}
function createDiagnostic(item: DiagnosticItem, doc: vscode.TextDocument) {
    if (item.line_index>= doc.lineCount) {
        console.error('got line that is larger than the line count', item.line_index);
        return null;
    }
    
    const lineOfText = doc.lineAt(item.line_index);
    let code = 'imdbug_' + item.line_index;
    
	const diagnostic = new vscode.Diagnostic(lineOfText.range, item.text, item.severity);
	diagnostic.code = code;
	return diagnostic;
}

export function refreshDocumentNow(diagnosticsCollection: vscode.DiagnosticCollection): void {
    if (vscode.window.activeTextEditor) {
		refreshDiagnostics(vscode.window.activeTextEditor.document, diagnosticsCollection);
	}
}

export function refreshModelNow(diagnosticsCollection: vscode.DiagnosticCollection, modelName: String): void {
    if (vscode.window.activeTextEditor) {
		refreshDiagnostics(vscode.window.activeTextEditor.document, diagnosticsCollection, modelName);
	}
}

export function subscribeToDocumentChanges(context: vscode.ExtensionContext, diagnosticsCollection: vscode.DiagnosticCollection): void {
    refreshDocumentNow(diagnosticsCollection);
    
	context.subscriptions.push(
		vscode.window.onDidChangeActiveTextEditor(editor => {
			if (editor) {
				refreshDiagnostics(editor.document, diagnosticsCollection);
            }
		})
	);
    // We have the option to run on every change in the file,  but opted to run only when a file is opened since it's for static repos:
	// context.subscriptions.push(
	// 	vscode.workspace.onDidChangeTextDocument(e => {
    //         refreshDiagnostics(e.document, diagnosticsCollection);
    //     })
	// );
    // instead, we use on save:
	context.subscriptions.push(
		vscode.workspace.onWillSaveTextDocument(e => {
             refreshDiagnostics(e.document, diagnosticsCollection);
         })
	 );

	context.subscriptions.push(
		vscode.workspace.onDidCloseTextDocument(doc => {
            diagnosticsCollection.delete(doc.uri);
        })
	);

}