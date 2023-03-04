import * as vscode from 'vscode';
import fetch from 'node-fetch';

const API_URL = 'http://968b-82-81-39-206.ngrok.io/analyze_code';

type DiagnosticItem = {
    // eslint-disable-next-line @typescript-eslint/naming-convention
    line_index: number;
    text: string;
    severity: vscode.DiagnosticSeverity;
};

function readDocumentProbs(doc: vscode.TextDocument) : Promise<Array<DiagnosticItem>> {

    return fetch(API_URL, {
        method: "POST",
        headers: {
            // eslint-disable-next-line @typescript-eslint/naming-convention
            "Content-Type": "application/json",
          },
        body: JSON.stringify({
            filename: doc.fileName,
            code: doc.getText(),
        })
    }).then(response => {
        if (!response.ok) {
          throw new Error(response.statusText);
        }
        return response.json();
      });
}

function refreshDiagnostics(doc: vscode.TextDocument, diagnosticsCollection: vscode.DiagnosticCollection): void {
    vscode.window.withProgress(
        { location: vscode.ProgressLocation.Notification, title: "imdbug: working on file" },
        async (_) => {
            const diagnostics: vscode.Diagnostic[] = [];
        
            const items = await readDocumentProbs(doc);
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