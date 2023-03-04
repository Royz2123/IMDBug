import * as vscode from 'vscode';
import { subscribeToDocumentChanges, refreshDocumentNow, getModels } from './diagnostics';

export function activate(context: vscode.ExtensionContext) {
	const models = getModels()
	const diagnosticsCollection = vscode.languages.createDiagnosticCollection("imdbug");
	context.subscriptions.push(diagnosticsCollection);

	subscribeToDocumentChanges(context, diagnosticsCollection);

	context.subscriptions.push(
		vscode.commands.registerCommand('imdbug.activate', () => {
			vscode.window.showInformationMessage('imdbug started working');
		})
	);

	context.subscriptions.push(
		vscode.commands.registerCommand('imdbug.refresh', () => {
			refreshDocumentNow(diagnosticsCollection);
		})
	);

	context.subscriptions.push(
		vscode.commands.registerCommand('imdbug.model', 
		async function () {
				const model = await vscode.window.showQuickPick(models, {
					matchOnDetail: true
				})
				console.log(model)
			}
			
		)
	)
}

export function deactivate() {}
