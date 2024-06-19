# Define parameters
param (
    [int]$prNumber
)

$repository = "pko-pako/Tech-Exercises"

# Check if user is logged into github
if (-not (gh auth status --hostname "github.com")){
	Write-Host "You're not authenticated, please login following the steps.`nIf you choose not to use credentials, faster authentication will be used."
	gh auth login --git-protocol HTTPS --hostname "github.com" --scopes 'workflow' --web
}

# Get the original pull request details
$sourcePr = gh pr view $prNumber --repo $repository --json headRefName,title,body,headRefOid | ConvertFrom-Json
$branch = $sourcePr.headRefName
$title = $sourcePr.title
$body = $sourcePr.body
$commitSha = $sourcePr.headRefOid

# Check if the name of the branch starts with "dependabot/"
$requiredPrefix = "dependabot/"
if (-not ($branch.StartsWith($requiredPrefix))) {
    Write-Host "PR branch does not start with '$requiredPrefix'. Exiting script."
    exit
}

# Close the original pull request
gh pr close --repo $repository $prNumber

# Wait for dependabot to delete the branch
Start-Sleep -Seconds 10.0

# Restore branch
gh api "repos/$repository/git/refs" -f ref="refs/heads/$branch" -f sha="$commitSha"
$exitCode = $LASTEXITCODE

# Check if the restore was successful
if ($exitCode -ne 0) {
	Write-Output "Unsuccessful restore of branch.`nPlease authorize again"
	gh auth login --git-protocol HTTPS --hostname "github.com" --scopes 'workflow' --web
	exit
}

# Create a new pull request for the new branch with the same title and body as the original
gh pr create --title "$title" --base main --repo "$repository" --head "$branch" -w
